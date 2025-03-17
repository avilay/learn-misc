from threading import Thread
import time


def fib(n):
    return fib(n - 1) + fib(n - 2) if n > 1 else n


def print_hello():
    while True:
        print("{} - Hello world!".format(int(time.time())))
        time.sleep(3)


def read_and_process_input():
    while True:
        n = int(input())
        print("fib({}) = {}".format(n, fib(n)))


def main():
    t = Thread(target=print_hello)
    t.daemon = True
    t.start()
    read_and_process_input()


if __name__ == '__main__':
    main()
