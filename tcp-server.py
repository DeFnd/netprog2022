import socket

PORT = 9996
BUFSIZE = 1024
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("",PORT))
s.listen(0)

connected = 1
while connected == 1:
    try:
        cnx, addr = s.accept()
    except:
        print("Error!!!")
        s.close()
        exit(1)
        
    print("get access from address ",addr)
    
    while True:
        msg = cnx.recv(BUFSIZE)
        msg = msg.decode("utf-8")
        print("client message: ",msg)
        if msg == "exit!":
            print("client disconnected ")
            break
      
        msg = input(">>> ")
        msg = msg.encode("utf-8")
        cnx.send(msg)
        
    if connected == 1:
        print("Still listen for the client ...")
    