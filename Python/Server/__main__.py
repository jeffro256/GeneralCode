from importlib import import_module
import os
import socket

from Server import *

def main():
    os.chdir(os.path.realpath(__file__).rsplit("/", 1)[0])

    print("Hosting at", HOST)

    PORT = askForInt("Port Number: ")

    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print("Socket created.")

    serversocket.bind((HOST, PORT))
    print("Socket bind succeeded.")

    BACKLOG = 10
    serversocket.listen(BACKLOG)
    print("Server now listening with a backlog of ", BACKLOG, "...", sep="")

    CLIENT_LOG_PATH = "logs/clientlog.txt"
    clientLog = open(CLIENT_LOG_PATH, "w")
    print("Opened client log file for writing.")

    DATA_BUFFER_LENGTH = 4096

    while True:
        try:
            connection, address = serversocket.accept()
            print("A connection has been established with ", address[0], ".", sep="")

            request = connection.recv(DATA_BUFFER_LENGTH)
            if not request:
                connection.close()
                print("Got empty request.")
                print("Closed connection to", address[0])
                continue

            requestedResource = getRawRequestedResource(request)
            print("Client requested resource: '", requestedResource, "'.", sep="")

            clientLog.write(request.decode())
            print("Wrote request to client log file.")

            resourcePath = getRequestedResourceAsPath(requestedResource)
            print("Path of resource:", resourcePath)

            requestDict = getRequestDict(request)
            print("Connection type is", requestDict["Connection"])

            if requestDict["Connection"] == "keep-alive":
                if resourcePath:
                    file = open(resourcePath, "rb")
                    fileContents = file.read()
                
                    connection.sendall(fileContents)
                    print("Sent '", resourcePath, "' to '", address[0], "'.", sep="")
                else:
                    sendError(404, "Not Found", connection)
                    print("Sent 404 error to", address[0])
            elif requestDict["Connection"] == "Upgrade" and requestDict["Upgrade"] == "websocket":
                if resourcePath:
                    fileName = resourcePath.rsplit(".", 1)[0]
                    modPath = "Server." + fileName.replace("/", ".")
                    
                    try:
                        key = requestDict["Sec-WebSocket-Key"]
                        sendWebSocketHeaders(key, connection)
                        wsHandleModule = import_module(modPath)
                        wsHandleModule.handle(connection, address)
                    except ImportError as ie:
                        print("Importing module", modPath, "failed.")
                        print(ie)
                        connection.sendall(b"HTTP/1.1 404 Not Found\r\n\r\n")
                    except Exception as e:
                        print("ERROR HAPPENED IN HANDLE FUNCTION IN MODULE:", modPath)
                        print(e)
                else:
                    connection.send(b"HTTP/1.1 404 Not Found\r\n\r\n")
            else:
                print("Connection to", address[0], "resulted in a bad request dictionary.")
                print("requestDict:", requestDict)
                sendError(501, "Not Implemented", connection)

            connection.close()
        except KeyboardInterrupt:
            print("Interrupted.")
            break

    clientLog.close()
    print("Closed client log file.")
    serversocket.close()
    print("Closed server socket.")
    print("Exiting...")

if __name__ == "__main__":
    main()
