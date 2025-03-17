#include <netdb.h>  // addrinfo, getaddrinfo, freeaddrinfo
#include <stdio.h>

#include "netutils.h"  // stringify_addrinfo

int main(const int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: netlearn hostname\n");
    return 1;
  }

  struct addrinfo hints = {0};
  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  struct addrinfo* res;
  const int status = getaddrinfo(argv[1], NULL, &hints, &res);
  if (status != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2;
  }

  printf(stringify_addrinfo(res));
  freeaddrinfo(res);

  puts("Done");
  return 0;
}
