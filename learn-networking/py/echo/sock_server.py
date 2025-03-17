from socket import socket, AF_INET, SOCK_STREAM
import click
import pretty_traceback
from cprint import warning_print

pretty_traceback.install()


@click.command()
@click.option("--port", default=45000, help="Port number")
def main(port):
    print(f"Starting server on 0.0.0.0:{port}")
    with socket(AF_INET, SOCK_STREAM) as s:
        s.bind(("", port))
        # Make a socket into a server socket that is listening for connections.
        # This call returns very quickly, so effectively is NOT a blocking call.
        s.listen()
        print("Started listening.")

        while True:
            print("\n\n**********************")
            # Socket must be bound and listening for connections in order to
            # accept connections. This is a blocking call. It will block until
            # there is a client connection to accept. The accept system call
            # returns a brand new socket (fd) with the client connecting on a
            # new port. In Python the addr return value contains a tuple of the
            # client's IP address and the new port that the OS has chosen for
            # this client.
            warning_print("Press ENTER to start accepting connections.")
            input()
            conn, addr = s.accept()
            print("Accepted a connection!")

            with conn:
                print("Client address ", addr)

                warning_print("Press ENTER to start receiving data.")
                input()
                data = conn.recv(1024)
                print("Data received.")

                warning_print("Press ENTER to start sending data.")
                input()
                conn.sendall(data)
                print("Data echoed back.")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
