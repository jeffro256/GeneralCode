import select
from websocket import client, getHeaders

def receiveAll(sock, timeout=10):
    dataParts = []

    while True:
        data = sock.recv(4096)

        if data:
           dataParts.append(data)
        else:
            break

    return b''.join(dataParts)

class MyHandler(client.WebSocketClientHandler):
    def handle(self):
        self.sendHeaders()
        returnData = receiveAll(self.connection)
        print(returnData)
        headers = getHeaders(returnData)

        if 'Sec-WebSocket-Accept' in headers and headers['Sec-WebSocket-Accept'] == self.getReturnKey():
            print("yay!")

if __name__ == '__main__':
    client = client.WebSocketClient('localhost', 8080, MyHandler)
    client.connect()
