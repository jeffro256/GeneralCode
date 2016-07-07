"""A module for working with the websocket protocol"""

from abc import ABCMeta, abstractmethod
from base64 import b64encode
from hashlib import sha1
from random import randrange

GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" #arbitrary string set by the ietf

WS_CONT  = 0
WS_TEXT  = 1
WS_BIN   = 2
WS_CLOSE = 8
WS_PING  = 9
WS_PONG  = 10

LEGAL_OPCODES = [WS_CONT, WS_TEXT, WS_BIN, WS_CLOSE, WS_PING, WS_PONG]

__all__ = ["encodeKey", "ClientWebSocket", "ServerWebSocket"]

class PayloadError(Exception):
    pass

class OpcodeError(Exception):
    pass

class BaseWebSocket(object):
    def receive(self):
        head = self.connection.recv(2)
        opcode = head[0] & 15
        lengthBits = head[1] & 127
        masked = head[1] >> 7
        fin = head[0] >> 7
        
        if opcode not in LEGAL_OPCODES:
            raise OpcodeError("Opcode '{}' in received message is not a valid opcode.".format(opcode))

        if lengthBits < 126:
            length = lengthByte
        elif lengthBits == 126:
            lengthBytes = self.connection.recv(2)
            length = _bytes_to_int(lengthBytes)
        else:
            lengthBytes = self.connection.recv(8)
            length = _bytes_to_int(lengthBytes)

        if masked:
            masks = self.connection.recv(4)
            maskedMsg = self.connection.recv(length)
            payload = _XOR_chars(maskedMsg, masks)
        else:
            payload = self.connection.recv(length)

        return payload.decode(), opcode if fin else (payload + self.receive()[0]).decode(), opcode

    def _send(self, msg, mask=False, opcode=WS_TEXT):
        length = len(msg)

        if opcode not in LEGAL_OPCODES:
            raise OpcodeError("Illegal opcode: '{}'".format(opcode))
        
        if length >= 2 ** 64:
            raise PayloadError("Payload length: '{}', is too big!".format(length))
        
        connection.sendall(_int_to_bytes(opcode | 128, 1))

        if length < 126:
            lengthByte = _int_to_bytes(length | 128 if mask else length, 1)
            self.connection.sendall(lengthByte)
        elif length < 2 ** 16:
            lengthByte = _int_to_bytes(126 | 128 if mask else 126, 1)
            self.connection.sendall(lengthByte)

            lengthBytes = _int_to_bytes(length, 2)
            self.connection.sendall(lengthBytes)
        else:
            lengthByte = _int_to_bytes(127 | 128 if mask else 127, 1)
            self.connection.sendall(lengthByte)

            lengthBytes = _int_to_bytes(length, 8)
            self.connection.sendall(lengthBytes)

        if mask:
            masks = _int_to_bytes(randrange(0, 2 ** 32), 4)
            self.connection.sendall(masks)

            payload = _XOR_chars(msg, masks)
            self.connection.sendall(payload)
        else:
            self.connection.sendall(msg.encode())

class ClientWebSocket(BaseWebSocket):
    def __init__(self, host, port):
        pass # ask for port
    
    def send(self, msg, opcode=1):
        self._send(msg, mask=True, opcode=opcode)

class ServerWebSocket(BaseWebSocket):
    def __init__(self, host, port):
        pass #listen on args
    
    def send(self, msg, mask=False, opcode=1):
        self._send(msg, mask=mask, opcode=opcode)

class BaseRequestHandler(object):
    __metaclass__ = ABCMeta

    def __init__(self, request, connection, address)
        self.request = request
        self.connection = connection
        self.address = address

        self.setup()
        try:
            self.handle()
        finally:
            self.finish()

    @abstractmethod
    def setup(self):
        pass
    
    @abstractmethod
    def handle(self):
        pass

    @abstractmethod
    def finish(self):
        pass

class WebSocketRequestHandler(BaseRequestHandler):
    def setup(self):
        pass

    def handle(self):
        pass

    def finish(self):
        pass

    def getKey(self):
        return

def encodeKey(key):
    if type(key) is bytes:
        return _encodeKey(key)
    elif type(key) is str:
        return _encodeKey(key.encode())
    else:
        raise ValueError("The type of key must be str or bytes")

"""Module functions"""

def _bytes_to_int(byteData):
    return int.from_bytes(byteData, byteorder="big", signed="False")

def _encodeKey_in(key):
    return b64encode(sha1(key + GUID.encode()).digest())

def _int_to_bytes(num, bytecount):
    return num.to_bytes(bytecount, byteorder='big')

def _XOR_charss(string, masks):
    return _XOR_chars(string, masks).decode()

def _XOR_chars(string, masks):
    newString = bytearray(len(string))
    
    for i, b in enumerate(string.encode() if type(string) == str else string):
        newString[i] = b ^ masks[i % len(masks)]

    return newString
