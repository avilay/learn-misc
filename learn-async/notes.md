Write a program to print "Hello World" every 3 seconds, and at the same time wait for input from the user. Each line of the user input will contain a single positive integer n. As soon as the number is entered, calculate and output the Fibonacci number and continue to wait for more input.

Now the trick is - while responding to the user input event, i.e., when calculating the fibonacci number - do not do anything else, i.e., do not keep printing "Hello World".

Why use asyncio?
================
Multithreaded program is the most performant, but it is hard to get right. The only other alternative before asyncio was to use sequential, single-threaded programming. asyncio is better than single-threaded, sequential programming, but worse than pure multi-threaded.

Task A runs for 4 ticks, after which it is waiting for some I/O that takes 6 ticks. It needs 2 more ticks after that to complete.
Task B runs for 7 ticks, after which it is waiting for some I/O that takes 2 ticks. It needs 2 more ticks to complete.


Multithreaded
-------------
In a pure multi-threaded model, the entire program will be done in 12 ticks.

```
A o----|      |--x
B o-------|  |--x
```

Sequential Single-Threaded
--------------------------
In a sequential single-threaded model it takes 23 ticks.

A o----|      |--x
B                o-------|  |--x

AsyncIO
-------
In the asyncio model, either A or B are running, both are not running simultaneously. However, when A is waiting, B starts to run and so on. It takes the entire program 15 ticks to run.

A o----|       |--x
B      o-------|  |--x