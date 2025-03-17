from socket import socket, AF_INET, SOCK_STREAM
import signal
import click


def alarm(x, y):
    raise TimeoutError()


signal.signal(signal.SIGALRM, alarm)


def timed_input(timeout):
    signal.alarm(timeout)
    try:
        ret = input()
        signal.alarm(0)
        return ret
    except TimeoutError:
        return None


def timed_recv(timeout, sock):
    signal.alarm(timeout)
    try:
        data = ""
        while True:
            data += sock.recv(1024).decode("utf-8")
            signal.alarm(0)
            if not data:
                break
        return data
    except TimeoutError:
        return None


@click.command()
@click.option("--port", default=45_000, help="Port number.")
@click.option("--server", default="127.0.0.1", help="Server address.")
def main(server, port):
    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect((server, port))
    while True:
        # check for user input
        msg = timed_input(1)
        if msg:
            sock.sendall(bytes(msg, encoding="utf-8"))

        # check for incoming messages
        msg = timed_recv(1, sock)
        if msg:
            print(msg.decode("utf-8"))


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
