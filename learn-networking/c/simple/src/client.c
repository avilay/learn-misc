//
// Created by avilay on 11/15/24.
//

#include "client.h"
#include <netdb.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXDATASIZE 100

int create_client_socket(const char* hostname, const char* port) {
  struct addrinfo* servinfo;

  struct addrinfo hints = {0};
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(hostname, port, &hints, &servinfo);
  iferr_die(status, "getaddrinfo:", gai_strerror(status));

  struct addrinfo* p;
  int sockfd = 0;
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if (sockfd != 0 && sockfd != -1) {
      close(sockfd);
    }

    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    iferr_continue(sockfd, "client: socket");

    status = connect(sockfd, p->ai_addr, p->ai_addrlen);
    iferr_continue(status, "client: connect");

    // Got a succesful socket, no need to at other addresses
    print_connx_details(p->ai_addr, "Client");
    break;
  }

  freeaddrinfo(servinfo);
  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    exit(4);
  }

  return sockfd;
}

void run_client(const char* hostname, const char* port) {
  int client_sock = create_client_socket(hostname, port);
  char buf[MAXDATASIZE];
  ssize_t num_bytes = recv(client_sock, buf, MAXDATASIZE-1, 0);
  iferr_die(num_bytes, "recv", NULL);
  buf[num_bytes] = '\0';

  printf("client: recieved %s\n", buf);

  close(client_sock);
}
