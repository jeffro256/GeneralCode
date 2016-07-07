import Server

def handle(connection, address):
    print("Handling...")
    while True:
        msg = Server.receiveFromWebSocket(connection)
        if not msg:
            print("No connection to '", address[0], "'.", sep="")
            break
        print("Message Received:", msg)
        Server.sendFromWebSocket(msg, connection)
