import socket

s = socket.socket()
s.bind(('127.0.0.1', 0))
s.connect(('4.4.8.8', 80))

s.sendall('''GET / HTTP/1.1
Host: www.google.com
Connection: keep-alive
Accept: text/html
Accept-Language: en-US

''')

print(s.recv(4096))