import socket

if __name__ == "__main__":
    host = "10.10.15.28"
    port = 6666
    addr = (host, port)

    c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:
        data = input("Enter a message: ")

        if data == "EXIT!":
            data = data.encode("utf-8")
            c.sendto(data, addr)

            print("Disconneted from the server.")
            break

        data = data.encode("utf-8")
        c.sendto(data, addr)

        data, addr = c.recvfrom(1024)
        data = data.decode("utf-8")
        print(f"Server: {data}")