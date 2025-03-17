from socket import socket, AF_INET, SOCK_STREAM
import click
import pretty_traceback
pretty_traceback.install()


@click.command()
@click.option("--server", default="127.0.0.1", help="Server address to connect to.")
@click.option("--port", default=45000, help="Server port to connect to.")
@click.argument("message")
def main(server, port, message):
    with socket(AF_INET, SOCK_STREAM) as s:
        # If the server is listening, this call will complete unless the server
        # is backlogged and refusing connections.
        s.connect((server, port))
        print("Connected to server.")

        # As long as the connection is established, the client can send its data
        # even if the server is not actively reading the data.
        s.sendall(bytes(message, encoding="utf-8"))
        print("Finished sending data.")

        # This is a blocking call and will only return once the client receives
        # data back from the server.
        data = s.recv(1024)
        print("Received ", repr(data))


if __name__ == "__main__":
    main()
