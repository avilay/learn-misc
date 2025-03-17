#include <locale.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static tells the CRT that this variable is shared amongst threads
// volatile tells the CRT to NOT use thread local cache, only main memory
static volatile int counter = 0;
const int OK = 0;

void *Task(void *arg) {
  printf("%s: begin looping %'d times\n", (char *)arg, (int)1e7);
  for (int i = 0; i < 1e7; i++) {
    counter = counter + 1;
  }
  printf("%s: done\n", (char *)arg);
  return NULL;
}

void WithThreads() {
  pthread_t t1, t2;
  int res;
  printf("main: begin (counter = %'d)\n", counter);

  res = pthread_create(&t1, NULL, Task, "A");
  if (res != OK) {
    printf("Unable to create thread A. Terminating.");
    exit(res);
  }

  res = pthread_create(&t2, NULL, Task, "B");
  if (res != OK) {
    printf("Unable to create thread B. Terminating.");
    exit(res);
  }

  res = pthread_join(t1, NULL);
  if (res != OK) {
    printf("WARN: Unable to join thread A. Skipping.");
  }

  res = pthread_join(t2, NULL);
  if (res != OK) {
    printf("WARN: Unable to join thread B. Skipping.");
  }

  printf("main: done with both (counter = %'d)\n", counter);
}

void WithoutThreads() {
  printf("main: begin (counter = %'d)\n", counter);
  Task("A");
  Task("B");
  printf("main: done with both (counter = %'d)\n", counter);
}

int PrintUsage() {
  printf("Usage:\n");
  printf("\t./race --threads\n");
  printf("\t./race --no-threads\n");
  return 1;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  if (argc < 2) {
    return PrintUsage();
  }
  if (strcmp(argv[1], "--threads") == 0) {
    WithThreads();
  } else if (strcmp(argv[1], "--no-threads") == 0) {
    WithoutThreads();
  } else {
    return PrintUsage();
  }
  return 0;
}
