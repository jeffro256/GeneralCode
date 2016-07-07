from base64 import b64encode
from hashlib import sha1
from socketserver import StreamRequestHandler

class WebSocketRequestHandler(StreamRequestHandler):
    def handle(self):
        pass
    
    def finish(self):
        closeMsg = "Closing..."
        self.rfile.send(bytes([128 | 8]))
        self.rfile.send(

    def send(self, msg, mask=True, opcode=WS_TEXT):
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
