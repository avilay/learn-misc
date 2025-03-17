// clang -Wall -o bin/hello hello.c

#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello, World!\n");
  for (int i = 0; i < argc; i++) {
    printf("[%d] %s\n", i, argv[i]);
  }
  return 0;
}
