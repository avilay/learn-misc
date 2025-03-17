# OS Concurrency

According to the course I have to include a `-pthread` flag to use pthread library as under -
```
gcc -o main main.c -Wall -pthread
```
But when using `clang` I don't seem to need it.

## Locks
There seem to be five types of thread locks based on the manpage of `pthread`:
  * mutex
  * mutex try lock
  * mutex timed lock
  * cond
  * rwlock

