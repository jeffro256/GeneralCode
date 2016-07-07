from hashlib import sha1
from base64 import b64encode
from os import urandom
import select
import socket

from . import BaseWebSocketInterface, WS_TEXT

HTTP_VERSION = '1.1'

class WebSocketClientInterface(BaseWebSocketInterface):
    def receive(self):
        return super().receive(needsMask=False)

    def send(self, msg, opcode=WS_TEXT):
        super().send(msg, opcode=opcode, needsMask=True)

class WebSocketClientHandler(object):
    def __init__(self, connection, address):
        self.connection = connection
        self.address = address

        self.setup()
        
        try:
            self.handle()
        finally:
            self.finish()

    def setup(self):
        self.rfile = self.connection.makefile('rb', buffering=-1)
        self.wfile = self.connection.makefile('wb', buffering=0)
        self.wsi = WebSocketClientInterface(self.rfile, self.wfile)
        self.key = self.generateKey()
    
    def handle(self):
        pass

    def finish(self):
        try:
            self.wfile.flush()
        finally:
            self.rfile.close()
            self.wfile.close()

    def sendHeaders(self, path='/', **extraHeaders):
        headers = ['GET {} HTTP/{}'.format(path, HTTP_VERSION).encode(),
                   b'Connection: Upgrade',
                   b'Upgrade: websocket',
                   'Sec-WebSocket-Key: {}'.format(self.key.decode()).encode()] + [
                   '{}: {}'.format(headerKey, extraHeaders[headerKey]).encode()
                        for headerKey in extraHeaders.keys()]

        sendData = b'\r\n'.join(headers) + b'\r\n\r\n'
        self.wfile.write(sendData)
        self.wfile.flush()

    def generateKey(self):
        return b64encode(urandom(16))

    def getReturnKey(self, key=None):
        if key is None:
            key = self.key

        GUID = '258EAFA5-E914-47DA-95CA-C5AB0DC85B11'
        return b64encode(sha1(key + GUID).digest())

class WebSocketClient(object):
    """Is a client, but works mostly like a server"""

    def __init__(self, host, port, handlerClass=WebSocketClientHandler):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.host = host
        self.port = port
        self.serverAddress = (host, port)
        self.handlerClass = handlerClass

    def connect(self):
        self.socket.connect(self.serverAddress)
        self.handler = self.handlerClass(self.socket, self.serverAddress)
