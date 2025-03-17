//
// Created by avilay on 11/15/24.
//

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void iferr_log(const int status, const char* msg_prefix, const char* msg) {
  if (status == -1) {
    msg_prefix = msg_prefix ? msg_prefix : "";
    if (msg == NULL) {
      perror(msg_prefix);
    } else {
      fprintf(stderr, "%s: %s\n", msg_prefix, msg);
    }
  }
}

void iferr_die(int status, const char* msg_prefix, const char* msg) {
  if (status == -1) {
    msg_prefix = msg_prefix ? msg_prefix : "";
    if (msg == NULL) {
      perror(msg_prefix);
    } else {
      fprintf(stderr, "%s: %s\n", msg_prefix, msg);
    }
    exit(1);
  }
}

void print_connx_details(const struct sockaddr* addr, const char* msg) {
  const void* address = NULL;
  char* ipver = NULL;
  in_port_t port;
  const int family = addr->sa_family;

  if (family == AF_INET) {
    const struct sockaddr_in* ipv4 = (struct sockaddr_in*)addr;
    address = &ipv4->sin_addr;
    port = ntohs(ipv4->sin_port);
    ipver = "IPv4";
  } else {
    const struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)addr;
    address = &ipv6->sin6_addr;
    port = ntohs(ipv6->sin6_port);
    ipver = "IPv6";
  }

  char ipstr[INET6_ADDRSTRLEN];
  inet_ntop(family, address, ipstr, sizeof ipstr);

  if (msg) {
    printf("%s - %s Connection: %s:%u\n", msg, ipver, ipstr, port);
  } else {
    printf("%s Connection: %s:%u\n", ipver, ipstr, port);
  }
}