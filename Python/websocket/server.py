import select
from socketserver import ThreadingTCPServer, StreamRequestHandler
from . import BaseWebSocketInterface, WS_TEXT

class WebSocketServer(ThreadingTCPServer):
    def verify_request(self, request, client_address):
        requestBytes = []
        timeout = 0.5
    
        while True:
            r, _, _ = select.select([request], [], [], timeout)

            if request not in r:
                break
            else:
                requestBytes.append(request.recv(4096))

        requestBytes = b''.join(requestBytes)
        requestDict = _get_dict_from_request(requestBytes.decode())

        if _is_ws_dict(requestDict):
            return True
        else:
            return False

    def finish_request(self, request, client_address):
        self.RequestHandlerClass(request, client_address, self, self.protocols)

class WebSocketServerInterface(BaseWebSocketInterface):
    def receive(self):
        return super(WebSocketServerInterface, self).receive(needsMask=False)

    def send(self, msg, opcode=WS_TEXT, masked=True):
        super(WebSocketServerInterface, self).send(msg, opcode=opcode, masked=masked)

class WebSocketServerRequestHandler(StreamRequestHandler):
    def __init__(self, request, client_address, server, protocols):
        super(WebSocketServerRequestHandler, self).__init__(request, client_address, server)
    
        self.protocols = protocols
    
    def setup(self):
        super(StreamRequestHandler, self).setup()

        self.wsi = WebSocketServerInterface(self.rfile, self.wfile)

def _get_dict_from_request(request):
    dataDict = {}
    lines = request.split('\n')

    for line in lines:
        try:
            parts = line.split(':')
            dataDict[parts[0].strip()] = parts[1].strip()
        except:
            continue

    return dataDict

def _dict_contains(sourceDict, subDict):
    for key in subDict.keys():
        if key not in sourceDict or sourceDict[key] != subDict[key]:
            return False

    return True

def _is_ws_dict(requestDict):
    subDict = {'Connection': 'Upgrade', 'Upgrade': 'websocket'}
    return _dict_contains(requestDict, subDict)
