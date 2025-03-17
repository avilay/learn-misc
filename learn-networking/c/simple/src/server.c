//
// Created by avilay on 11/14/24.
//

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"

#define BACKLOG 5


// To reap zombie child processes
void sigchld_handler(int sig) {
  const int saved_errno = errno;
  while(waitpid(-1, 0, WNOHANG) > 0) {}
  errno = saved_errno;
}

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
  // To reap zombie child processes
  struct sigaction sa;
  sa.sa_handler = sigchld_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  iferr_die(
    sigaction(SIGCHLD, &sa, NULL),
    "sigaction:",
    NULL
  );

  const int server_sock = create_server_socket(port);
  iferr_die(
    listen(server_sock, BACKLOG),
    "listen:",
    NULL
  );

  printf("server: waiting for connections...\n");

  while(1) {
    struct sockaddr_storage client_addr;
    socklen_t sin_size = sizeof client_addr;
    const int data_sock = accept(server_sock, (struct sockaddr *)&client_addr, &sin_size);
    iferr_continue(data_sock, "accept");

    print_connx_details((struct sockaddr*)&client_addr, "Got client");

    if (fork() == 0) {
      // this is the child process
      close(server_sock);  // child does not need the control plane socket
      iferr_log(
        send(data_sock, "Hello, World!", 13, 0),
        "send:",
        NULL
      );
      close(data_sock);
      exit(0);
    }
    // back in the parent process
    close(data_sock);
  }
}
