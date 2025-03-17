//
// Created by avilay on 11/14/24.
//
#include "stringutils.h"
#include "netutils.h"

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

char* stringify_ai_protocol(const int proto) {
  const struct protoent* p = getprotobynumber(proto);
  if (p == NULL) {
    return "unknown";
  }
  char* protoname = strdup(p->p_name);
  return protoname;
}

char* stringify_ai_socktype(const int socktype) {
  switch (socktype) {
    case SOCK_DGRAM:
      return "UDP";
    case SOCK_STREAM:
      return "TCP";
    case SOCK_RAW:
      return "RAW";
    case SOCK_SEQPACKET:
      return "SEQPACKET";
    case SOCK_RDM:
      return "RDM";
    case SOCK_PACKET:
      return "PACKET";
    default:
      return "UNKNOWN";
  }
}

char* stringify_ai_family(const int family) {
  switch (family) {
    case AF_INET:
      return "AF_INET";
    case AF_INET6:
      return "AF_INET6";
    case AF_UNIX:
      return "AF_UNIX";
    default:
      return "UNKNOWN";
  }
}

char* stringify_ai_flags(const int flags) {
  char* str_flags = strdup("");
  if (flags == 0) {
    append_str_to_str(&str_flags, "<NONE>");
  }
  if (flags == AI_PASSIVE) {
    append_str_to_str(&str_flags, "AI_PASSIVE");
  }
  if (flags == AI_CANONNAME) {
    append_str_to_str(&str_flags, "AI_CANONNAME");
  }
  if (flags == AI_NUMERICHOST) {
    append_str_to_str(&str_flags, "AI_NUMERICHOST");
  }
  if (flags == AI_V4MAPPED) {
    append_str_to_str(&str_flags, "AI_V4MAPPED");
  }
  if (flags == AI_ALL) {
    append_str_to_str(&str_flags, "AI_ALL");
  }
  if (flags == AI_ADDRCONFIG) {
    append_str_to_str(&str_flags, "AI_ADDRCONFIG");
  }
  return str_flags;
}

char* stringify_ai_addr(const struct sockaddr* addr) {
  const void* address = NULL;
  char* ipver = NULL;
  in_port_t port;
  int family = addr->sa_family;

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

  char* buf = NULL;
  asprintf(&buf, "%s %s:%u\n", ipver, ipstr, port);
  return buf;
}

char* stringify_addrinfo(const struct addrinfo* res) {
  char* buf = strdup("\nADDRINFO --");

  append_str_to_str(&buf, "\nai_flags = ");
  append_str_to_str(&buf, stringify_ai_flags(res->ai_flags));

  append_str_to_str(&buf, "\nai_family = ");
  append_str_to_str(&buf, stringify_ai_family(res->ai_family));

  append_str_to_str(&buf, "\nai_socktype = ");
  append_str_to_str(&buf, stringify_ai_socktype(res->ai_socktype));

  append_str_to_str(&buf, "\nai_protocol = ");
  append_str_to_str(&buf, stringify_ai_protocol(res->ai_protocol));

  append_str_to_str(&buf, "\nai_addrlen = ");
  append_uint_to_str(&buf, res->ai_addrlen);

  append_str_to_str(&buf, "\nai_canonname = ");
  append_str_to_str(&buf, res->ai_canonname);

  append_str_to_str(&buf, "\nai_addr = ");
  append_str_to_str(&buf, stringify_ai_addr(res->ai_addr));

  append_str_to_str(&buf, "\n");

  if (res->ai_next != NULL) {
    append_str_to_str(&buf, stringify_addrinfo(res->ai_next));
  }
  return buf;
}
