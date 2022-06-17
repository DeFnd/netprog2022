import socket

PORT = 9996
BUFSIZE=1024

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("localhost",PORT))

while True:
    msg = input(">  ")
    
    if msg ==  "exit!":
        msg = msg.encode("utf-8")
        s.send(msg)
        print(" Client disconnected! ")
        break

    msg = msg.encode("utf-8")
    s.send(msg)
    
    msg = s.recv(BUFSIZE)
    msg = msg.decode("utf-8")
    print("Server message: ",msg)
    
s.close()