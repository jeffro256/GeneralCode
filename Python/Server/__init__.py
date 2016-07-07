import base64
import hashlib
import os.path
import socket

HOST = socket.gethostbyname(socket.gethostname())
PORT = 8080 # arbitrary number that might actually be used as a real port number

def askForInt(askStr):
    while True:
        try:
            inputInt = int(input(askStr))
            break
        except ValueError:
            print("Input was not an integer. Try Again.")

    return inputInt

def getRawRequestedResource(byteData):
    firstLine = byteData.split(b"\r\n")[0]
    secondWord = firstLine.split()[1]
    
    return secondWord.decode()

def getRequestDict(byteData):
    strData = byteData.decode()
    lines = strData.split("\r\n")[1:]
    requestDict = {}
    
    for line in lines:
        splitLine = line.split(":")
        
        if len(splitLine) >= 2:
            requestDict[splitLine[0].strip()] = ":".join(splitLine[1:]).strip()

    return requestDict

def sendWebSocketHeaders(key, connection):
    connection.sendall(b"HTTP/1.1 101 Switching Protocols\r\n")
    connection.sendall(b"Upgrade: websocket\r\n")
    connection.sendall(b"Connection: Upgrade\r\n")
    
    GUID = b"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
    newKey = base64.b64encode(hashlib.sha1(key.encode() + GUID).digest())
    
    connection.sendall(b"Sec-WebSocket-Accept: " + newKey + b"\r\n\r\n")

def sendFromWebSocket(msg, ws):
    ws.send(bytes([129]))
    length = len(msg)
    
    if length <= 125:
        ws.send(bytes([length]))
    elif length <= 65535:
        ws.send(bytes([126]))
        ws.send(length.to_bytes(2, byteorder="big"))
    else:
        ws.send(bytes([127]))
        ws.send(length.to_bytes(8, byteorder="big"))
    
    ws.send(msg.encode())

def receiveFromWebSocket(ws):
    head = ws.recv(2)
    
    if head[0] & 0b00001111 == 8:
        return ""
    
    masked = (head[1] & 0b10000000) == 0b10000000
    
    if not masked:
        return
    
    lengthOfData = head[1] & 0b01111111
    if lengthOfData == 126:
        raw = ws.recv(2)
        lengthOfData = bytesToInt(raw)
    elif lengthOfData == 127:
        raw = ws.recv(8)
        lengthOfData = bytesToInt(raw)

    masks = ws.recv(4)

    print("length of data:", lengthOfData)
    
    payload = ws.recv(lengthOfData)
    
    payloadDemasked = bytearray(lengthOfData)
    for i, b in enumerate(payload):
        payloadDemasked[i] = b ^ masks[i % 4]
    
    return payloadDemasked.decode()

def bytesToInt(byteData):
    return int.from_bytes(byteData, byteorder="big", signed="False")

def sendError(errorCode, errorDescription, connection):
    errorTemplatePath = "error/errorTemplate.html"
    errorTemplateFile = open(errorTemplatePath)
    errorTemplateContents = errorTemplateFile.read()
    package = errorTemplateContents.format(code=errorCode, msg=errorDescription)

    connection.sendall("HTTP/1.1 {code} {msg}\n".format(code=errorCode, msg=errorDescription).encode())
    connection.sendall("Content-Length: {}\n".format(len(package)).encode())
    connection.sendall(b"Content-Type: text/html\n\n")
    connection.sendall(package.encode())

def getRequestedResourceAsPath(request):
    request = request.strip("/")
    if not request:
        return "index.html"
    elif isHiddenFile(request):
        return ""
    elif os.path.exists(request):
        if os.path.isfile(request):
            return request
        elif os.path.exists(request + "/index.html"):
            return request + "/index.html"
        else:
            return ""
    else:
        return ""

def isHiddenFile(path):
    hiddenPaths = ("__pycache__", "clientlog.txt")
    
    if path.endswith(".py") or path.endswith(".pyc") or path.endswith(".bak"):
        return True
    
    for hPath in hiddenPaths:
        if hPath in path:
            return True
    
    return False
