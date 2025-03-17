//
// Created by avilay on 11/15/24.
//

// #include "server.h"

#include <assert.h>
#include <errno.h> //
#include <netdb.h> //
#include <poll.h>
#include <stdio.h> //
#include <stdlib.h> //
#include <unistd.h> //
#include <sys/socket.h> //

#include "utils.h"

typedef struct Sockets {
  struct pollfd* fds;
  int capacity;
  int count;
} Sockets;

int add_socket(Sockets* sockets, const int fd) {
  if (sockets->count == sockets->capacity) {
    sockets->capacity *= 2;
    struct pollfd* old_fds = sockets->fds;
    sockets->fds = malloc(sizeof(struct pollfd) * sockets->capacity);
    if (sockets->fds == NULL) {
      sockets->fds = old_fds;
      errno = ENOMEM;
      return -1;
    }
  }
  assert(sockets->count < sockets->capacity);
  sockets->fds[sockets->count].fd = fd;
  sockets->fds[sockets->count].events = POLLIN;
  sockets->count += 1;
  return 0;
}

void cleanup_socket(Sockets* sockets, const int nbytes, const int idx) {
  struct pollfd bad = sockets->fds[idx];
  if (nbytes == 0) {
    printf("Client on socket %d closed connection.\n", bad.fd);
  } else if (nbytes == -1) {
    perror("recv");
  }
  close(bad.fd);
  printf("DEBUG: Closed socket %d\n", bad.fd);
  // Remove this socket by overwriting the last one on top of this one
  sockets->fds[idx] = sockets->fds[sockets->count-1];
  sockets->count -= 1;
}

int _create_server_socket(const char* port) {
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


void _start_server(const char* port) {
  const int initial_cap = 5;
  Sockets sockets = {
    .fds = malloc(sizeof(struct pollfd) * initial_cap),
    .capacity = initial_cap,
    .count = 0
  };

  const int server_sock = _create_server_socket(port);
  add_socket(&sockets, server_sock);
  const int status = listen(server_sock, 10);
  iferr_die(status, "Unable to listen", NULL);

  // Main loop
  for(;;) {
    const int num_ready = poll(sockets.fds, sockets.count, -1);
    iferr_die(num_ready, "poll", NULL);

    // Check if there is a new connx on the server socket, it is always the first socket.
    if (sockets.fds[0].revents & POLLIN) {
      assert(sockets.fds[0].fd == server_sock);

      struct sockaddr_storage client_addr;
      socklen_t addrlen = sizeof(client_addr);
      int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addrlen);
      iferr_log(client_sock, "accept", NULL);

      add_socket(&sockets, client_sock);
      print_connx_details((struct sockaddr*)&client_addr, "New client connection: ");
      printf("Using socket %d\n", client_sock);
    }

    // Check if any of the existing clients have sent anything.
    for(int i = 1; i < sockets.count; i++) {
      struct pollfd client = sockets.fds[i];
      if (client.revents & POLLIN) {
        char buf[256];
        int nbytes = recv(client.fd, buf, sizeof(buf), 0);
        if (nbytes <= 0) {
          cleanup_socket(&sockets, nbytes, i);
        } else {
          // Broadcast the message
          for(int j = 0; j < sockets.count; j++) {
            struct pollfd dest = sockets.fds[j];
            if (dest.fd != server_sock && dest.fd != client.fd) {
              nbytes = send(dest.fd, buf, nbytes, 0);
              iferr_log(nbytes, "broadcast error!", NULL);
            }
          }
        }
      }
    }
  }
}
