import sys
import time
import selectors


def fib(n):
    return fib(n - 1) + fib(n - 2) if n > 1 else n


def process_input(stream):
    text = stream.readline()
    n = int(text.strip())
    print('fib({}) = {}'.format(n, fib(n)))


def print_hello():
    print('{} - Hello world!'.format(time.time()))


def main():
    selector = selectors.DefaultSelector()
    selector.register(sys.stdin, selectors.EVENT_READ)
    last_hello = 0
    while True:
        for event, mask in selector.select(0.1):
            process_input(event.fileobj)
        if time.time() - last_hello > 3:
            last_hello = time.time()
            print_hello()


if __name__ == '__main__':
    main()
