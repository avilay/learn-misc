#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "client.h"
#include "server.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Usage: %s <server|client> <hostname> <port>\n", argv[0]);
    return 1;
  }

  const long maybe_port = strtol(argv[3], NULL, 10);
  if (maybe_port > 65535 || maybe_port < 1024) {
    fprintf(stderr, "invalid port %ld\n", maybe_port);
    return 2;
  }

  if (strcmp(argv[1], "server") == 0) {
    start_server(argv[3]);
  } else if (strcmp(argv[1], "client") == 0) {
    run_client(argv[2], argv[3]);
  } else {
    fprintf(stderr, "Usage: %s <server|client> <port>\n", argv[0]);
    return 3;
  }

  return 0;
}
