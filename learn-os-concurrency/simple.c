// clang -Wall -o bin/simple_threads simple_threads.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

const int OK = 0;

void *Task(void *arg) {
  char *val = (char *)arg;
  printf("Doing task with %s\n", val);
  return NULL;
}

int main(int argc, char *argv[]) {
  int res = -1;
  pthread_t t1, t2;
  printf("Starting main\n");

  // Create a thread and start executing it
  // pthread_t *: Return the thread handle here
  // const pthread_attr_t *attr: NULL means use default attributes for this
  // thread
  // void *(*func)(void *): Function pointer that the thread should
  // execute
  // void *: Argument to pass to thread. "A" is somehow automatically
  // cast to void *?
  res = pthread_create(&t1, NULL, Task, "A");
  if (res != OK) {
    printf("Unable to create thread! Terminating. {%d}", res);
    exit(res);
  }

  res = pthread_create(&t2, NULL, Task, "B");
  if (res != OK) {
    printf("Unable to create thread! Terminating. {%d}", res);
    exit(res);
  }

  // Wait for t1 to complete
  // pthread_t: Thread handle of the thread to wait for
  // void **: The return value of the thread function will be available here
  // If the thread is returning NULL (as Task does), then just pass NULL here.
  res = pthread_join(t1, NULL);
  if (res != OK) {
    printf("Unable to join thread A! Skipping. {%d}", res);
  }

  res = pthread_join(t2, NULL);
  if (res != OK) {
    printf("Unable to join thread B! Skipping. {%d}", res);
  }

  printf("Main complete\n");
  return 0;
}