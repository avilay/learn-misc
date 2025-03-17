//
// Created by avilay on 11/16/24.
//
#include "server.h"

#include <assert.h>
#include <errno.h> //
#include <netdb.h> //
#include <poll.h>
#include <stdio.h> //
#include <stdlib.h> //
#include <unistd.h> //
#include <sys/socket.h> //
#include <glib.h>

#include "utils.h"

int create_server_socket(const char* port) {
  struct addrinfo hints = {0};
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo* servinfo;

  int status = getaddrinfo(NULL, port, &hints, &servinfo);
  iferr_die(status, "getaddrinfo:", gai_strerror(status));

  const int yes = 1;
  struct addrinfo* p = NULL;
  int sockfd = 0;
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if (sockfd != -1 && sockfd != 0) close(sockfd);

    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    iferr_continue(sockfd, "server: socket");

    iferr_die(
      setsockopt(
        sockfd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &yes,
        sizeof(int)),
      "setsockopt:",
      NULL
    );

    status = bind(sockfd, p->ai_addr, p->ai_addrlen);
    iferr_continue(status, "server: bind");

    // Got a successful socket, no need to look at other address infos.
    print_connx_details(p->ai_addr, "Server");
    break;
  }

  freeaddrinfo(servinfo);
  if (p == NULL) {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
  }

  return sockfd;
}

void start_server(const char* port) {
  puts("Starting server ver 2");

  const int initial_cap = 8;
  GArray* fds = g_array_sized_new(FALSE, FALSE, sizeof(struct pollfd), initial_cap);

  const int server_sock = create_server_socket(port);
  struct pollfd server = {.fd = server_sock, .events = POLLIN};
  g_array_append_val(fds, server);

  const int status = listen(server_sock, 10);
  iferr_die(status, "Unable to listen", NULL);

  // Main loop
  for(;;) {
    const int num_ready = poll((struct pollfd*)fds->data, fds->len, -1);
    iferr_die(num_ready, "poll", NULL);

    // Check if there is a new connx on the server socket, it is always the first socket.
    server = g_array_index(fds, struct pollfd, 0);
    assert(server.fd == server_sock);
    if (server.revents & POLLIN) {
      struct sockaddr_storage client_addr;
      socklen_t addrlen = sizeof(client_addr);
      int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addrlen);
      iferr_log(client_sock, "accept", NULL);

      struct pollfd new_client = {.fd = client_sock, .events = POLLIN};
      g_array_append_val(fds, new_client);

      print_connx_details((struct sockaddr*)&client_addr, "New client connection: ");
      printf("Using socket %d\n", client_sock);
    }

    // Check if any of the existing clients have sent anything
    for(int i = 1; i < fds->len; i++) {
      struct pollfd client = g_array_index(fds, struct pollfd, i);
      if (client.revents & POLLIN) {
        char buf[256];
        long nbytes = recv(client.fd, buf, sizeof(buf), 0);
        if (nbytes <= 0) {
          // Clean up this client
          if (nbytes == 0) {
            printf("Client on socket %d closed connection\n", client.fd);
          } else if (nbytes == -1) {
            perror("recv");
          }
          close(client.fd);
          g_array_remove_index(fds, i);
        } else {
          // Broadcast the message
          for(int j = 1; j < fds->len; j++) {
            struct pollfd dest = g_array_index(fds, struct pollfd, j);
            if (dest.fd != client.fd) {
              nbytes = send(dest.fd, buf, nbytes, 0);
              iferr_log(nbytes, "send", NULL);
            }
          }
        }
      }
    }
  }
}
