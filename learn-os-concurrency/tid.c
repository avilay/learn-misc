/*
There does not seem to be a good way to represent pthread_t. On MacOS it is a
struct that looks like -

typedef __darwin_pthread_t pthread_t;

struct _opaque_pthread_t {
        long __sig;
        struct __darwin_pthread_handler_rec  *__cleanup_stack;
        char __opaque[__PTHREAD_SIZE__];
};

typedef struct _opaque_pthread_t *__darwin_pthread_t;

Here I am using tid->__sig but this is not at all portable!

See
https://stackoverflow.com/questions/21091000/how-to-get-thread-id-of-a-pthread-in-linux-c-program
for a good discussion.
*/

#include <pthread.h>
#include <stdio.h>

void *Task(void *arg) {
  pthread_t tid = pthread_self();
  char *val = (char *)arg;
  printf("[%ld] Starting task with %s\n", tid->__sig, val);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, Task, "A");
  pthread_create(&t2, NULL, Task, "B");
  pthread_join(t1, NULL);
  return 0;
}
