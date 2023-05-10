import socket

IP = 'localhost'
PORT = 7777


def open_socket(ip, port):
    """Opens a socket for the client

    :param ip: the server's ip address
    :type ip: str
    :param port: the port of the server
    :type port: int
    :return: the socket of the client
    :rtype: socket
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))

    return sock


def main():
    try:
        sock = open_socket(IP, PORT)
    except ConnectionRefusedError as connection_err:
        print("Unable to connect to server! more info:", connection_err)
        input()
        return

    code = '0'
    message = '{"username": "gamer123","password": "pass123"}'
    size = str(len(message)).zfill(4)
    request = code + size + message 

    sock.sendall(request.encode())
    sock.close()


if __name__ == "__main__":
    main()
