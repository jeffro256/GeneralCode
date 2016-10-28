import datetime
import socket
from sys import argv
import threading
from time import sleep

def broadcastAlive():
    ip = "<broadcast>"
    port = 8989
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    while True:
        msg_prefix = "22AF4240=" # Bon Iver - 22, A Million
        msg = msg_prefix + datetime.datetime.now().strftime("%A %d %H:%M:%S -- ") + socket.gethostname()
        sock.sendto(msg.encode(), (ip, port))
        sleep(5)

def broadcastThread():
    bt = threading.Thread(target=broadcastAlive)
    bt.daemon = False # True

    return bt

broadcastThread().start()
