import socket
from time import sleep

HOST = socket.gethostbyname(socket.gethostname())
PORT = 9090
while True:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))

        sleep(1)
        while True:
            x = input("enter text: ")
            s.send(bytes(x, 'utf-8'))
            print('sent')
            sleep(0.1)
