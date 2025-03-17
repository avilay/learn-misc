import heapq as hq
from selectors import DefaultSelector
import selectors
from time import time
import sys


def fib(n):
    return fib(n - 1) + fib(n - 2) if n > 1 else n


class Timer:
    def __init__(self, timestamp, handler):
        self.timestamp = timestamp
        self.handler = handler
        
    def __lt__(self, other):
        return self.timestamp < other.timestamp
    
    def __le__(self, other):
        return self.timestamp <= other.timestamp
    
    def __eq__(self, other):
        return self.timestamp == other.timestamp
    
    def __ge__(self, other):
        return self.timestamp >= other.timestamp
    
    def __gt__(self, other):
        return self.timestamp > other.timestamp
    
    def __ne__(self, other):
        return self.timestamp != other.timestamp
    
    def __str__(self):
        return 'Timestamp: {}  Handler: {}'.format(self.timestamp, self.handler)


class EventLoop:
    def __init__(self):
        self._running = False
        self._stdin_handlers = []
        self._timers = []
        self._selector = DefaultSelector()
        self._selector.register(sys.stdin, selectors.EVENT_READ)

    def run_forever(self):
        self._running = True
        while self._running:
            # First handle any IO if available
            for key, mask in self._selector.select(0):
                line = key.fileobj.readline().strip()
                for callback in self._stdin_handlers:
                    callback(line)

            # Now handle any timers that have tripped
            while len(self._timers) > 0 and self._timers[0].timestamp < time():
                timer = hq.heappop(self._timers)
                timer.handler()

    def add_stdin_handler(self, callback):
        self._stdin_handlers.append(callback)

    def add_timer(self, wait_time, callback):
        hq.heappush(self._timers, Timer(time() + wait_time, callback))

    def stop(self):
        self._running = False


def main():
    loop = EventLoop()

    def on_stdin_input(line):
        if line == 'exit':
            loop.stop()
            return
        n = int(line)
        print('fib({}) = {}'.format(n, fib(n)))

    def print_hello():
        print('{} - Hello world!'.format(int(time())))
        loop.add_timer(3, print_hello)

    loop.add_stdin_handler(on_stdin_input)
    loop.add_timer(0, print_hello)
    loop.run_forever()


if __name__ == '__main__':
    main()










