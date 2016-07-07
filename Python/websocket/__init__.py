from random import randrange

__all__ = ["BaseWebSocketInterface", "getHeaders", "WS_CONT", "WS_TEXT", "WS_BIN", "WS_CLOSE",
           "WS_CLOSE", "WS_PING", "WS_PONG", "client", "server"]

WS_CONT  = 0
WS_TEXT  = 1
WS_BIN   = 2
WS_CLOSE = 8
WS_PING  = 9
WS_PONG  = 10

class MaskError(Exception):
    pass

class OpcodeError(Exception):
    pass

class PayloadError(Exception):
    pass

class BaseWebSocketInterface(object):
    LEGAL_OPCODES = [WS_CONT, WS_TEXT, WS_BIN, WS_CLOSE, WS_PING, WS_PONG]

    def __init__(self, rfile, wfile):
        if "b" not in rfile.mode or "b" not in wfile.mode:
            raise ValueError('Files passed in as arguments are not in binary mode.')
        
        self.rfile = rfile
        self.wfile = wfile

    def receive(self, needsMask=False):
        head = self.rfile.read(2)
        opcode = head[0] & 15
        lengthBits = head[1] & 127
        masked = head[1] >> 7
        fin = head[0] >> 7
    
        if opcode not in LEGAL_OPCODES:
            raise OpcodeError('Opcode {} in received message is not a valid opcode.'.format(opcode))

        if not masked and needsMask:
            raise MaskError('Message needs to be masked but is not.')

        if lengthBits < 126:
            lengthBytes = bytes([lengthBits])
        elif lengthBits == 126:
            lengthBytes = self.rfile.read(2)
        else:
            lengthBytes = self.rfile.read(8)

        length = _bytes_to_int(lengthBytes)
        
        if masked:
            masks = self.rfile.read(4)
            maskedMsg = self.rfile.read(length)
            payload = _XOR_chars(maskedMsg, masks)
        else:
            payload = self.rfile.read(length)

        return payload.decode(), opcode if fin else (payload + self.receive()[0]).decode(), opcode

    def send(self, msg, opcode=WS_TEXT, masked=True):
        length = len(msg)

        if opcode not in LEGAL_OPCODES:
            raise OpcodeError('Illegal Opcode: {}'.format(opcode))

        if length >= 2 ** 64:
            raise PayloadError('Payload Length: {}, is too big!'.format(length))

        self.wfile.write(bytes([opcode | 128]))

        if length < 126:
            lengthBytes = bytes([(length | 128) if mask else length])
        elif length < 2 ** 16:
            lengthBytes = bytes([(126 | 128) if mask else 126]) + _int_to_bytes(length, 2)
        else:
            lengthBytes = bytes([(127 | 128) if mask else 127]) + _int_to_bytes(length, 8)

        self.wfile.write(lengthBytes)

        if mask:
            masks = _int_to_bytes(randrange(0, 2 ** 32), 4)
            self.wfile.write(masks)

            payload = _XOR_chars(msg, masks)
            self.wfile.write(payload)
        else:
            self.wfile.write(msg.encode())

def getHeaders(text):
    if type(text) == bytes:
        text = text.decode()

    lines = text.split("\n")
    headers = {}

    for line in lines:
        parts = line.split(":")

        try:
            headers[parts[0].strip()] = parts[1].strip()
        except IndexError:
            continue

    return headers

def _bytes_to_int(byteData):
    return int.from_bytes(byteData, byteorder="big", signed="False")

def _int_to_bytes(num, bytecount):
    return num.to_bytes(bytecount, byteorder='big')

def _XOR_chars(string, masks):
    newString = bytearray(len(string))
    
    for i, b in enumerate(string.encode() if type(string) == str else string):
        newString[i] = b ^ masks[i % len(masks)]
    
    return newString
