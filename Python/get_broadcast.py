import socket
from sys import argv

port = 8989

if len(argv) < 2:
    print("No port specified, defaulting to port", port, "...")
else:
    port = int(argv[1])

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(("", port))

while True:
    try:
        msg_prefix = "22AF4240=" # Bon Iver - 22, A Million
        msg = sock.recvfrom(1024)[0].decode()

        if msg.startswith(msg_prefix):
            print(msg[len(msg_prefix):])
    except KeyboardInterrupt:
        break

print()
sock.close()
