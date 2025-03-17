from socket import SOCK_STREAM, socket, AF_INET, SOCK_DGRAM
import selectors
import click
import pretty_traceback
pretty_traceback.install()

selector = selectors.DefaultSelector()

def accept(sock, mask):
    conn, addr = sock.accept()
    print("Client address ", addr)
    conn.setblocking(False)
    selector.register(conn, selectors.EVENT_READ, read)


def read(sock, mask):
    data = sock.recv(1024)
    print("Data received.")
    print(mask)
    if data:
        sock.send(data)
        print("Data echoed back.")
    else:
        print("No more data")
        selector.unregister(sock)
        sock.close()    


@click.command()
@click.option("--port", default=45000, help="Port number")
def main(port):
    with socket(AF_INET, SOCK_STREAM) as listener:
        listener.bind(("", port))
        listener.listen()
        listener.setblocking(False)
        selector.register(listener, selectors.EVENT_READ, accept)
        while True:
            for key, mask in selector.select(0.1):
                callback = key.data
                callback(key.fileobj, mask)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass