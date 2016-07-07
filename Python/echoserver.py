import select
import socket
import sys

from websocket import getHeaders

def main():
    host = sys.argv[1]
    port = int(sys.argv[2])
    backlog = 5

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(backlog)

    print('Listening at ({}, {}) with a backlog of {}.'.format(host, port, backlog))

    try:
        while True:
            conn, addr = s.accept()

            requestData = conn.recv(4096)

            if b'GET' in requestData.split(b'\n')[0]:
                requestData = b'HTTP/1.1 200 OK\r\n' + b'\r\n'.join(requestData.split(b'\n')[1:]).strip()
                headers = getHeaders(requestData)
                print(headers)

                if 'Sec-WebSocket-Key' in headers:
                    from base64 import b64encode
                    from hashlib import sha1

                    print('doing key stuff')

                    key = headers['Sec-Websocket-Key'].encode()
                    GUID = b'258EAFA5-E914-47DA-95CA-C5AB0DC85B11'
                    returnKey = b64encode(sha1(key + GUID).digest())

                    requestData += b'Sec-WebSocket-Accept: ' + returnKey + b'\r\n\r\n'

            print("Sending:", requestData)
            conn.sendall(requestData)
            conn.close()
    except Exception as e:
        print(e)
        conn.close()
        s.close()

def getFullDataFrom(sock, timeout=0.5):
    dataList = []

    while True:
        data = sock.recv(4096)

        if data:
            print('meh')
            dataList.append(data)
        else:
            break

    return b''.join(dataList)

if __name__ == '__main__':
    main()

