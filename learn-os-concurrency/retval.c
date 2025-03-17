// clang -Wall -o bin/retval_threads retval_threads.c

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *Task(void *arg) {
  char *task_id = (char *)arg;
  int *sleep_secs = (int *)malloc(sizeof(int));
  *sleep_secs = random() % 5;
  printf("[%s] Sleeping for %d secs\n", task_id, *sleep_secs);
  sleep(*sleep_secs);
  printf("[%s] Task complete\n", task_id);
  return sleep_secs;
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2;
  printf("Starting main\n");
  pthread_create(&t1, NULL, Task, "A");
  pthread_create(&t2, NULL, Task, "B");
  int *t1_retval, *t2_retval;
  pthread_join(t1, (void **)&t1_retval);
  pthread_join(t2, (void **)&t2_retval);
  printf("T1 returned %d\n", *t1_retval);
  printf("T2 returned %d\n", *t2_retval);
  free(t1_retval);
  free(t2_retval);
  printf("Main complete\n");
  return 0;
}