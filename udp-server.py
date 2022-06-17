import socket

if __name__ == "__main__":
    host = ""
    port = 8888

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(("", port))

    while True:
        data, addr = s.recvfrom(1024)
        data = data.decode("utf-8")
        print(data)

        if data == "EXIT!":
            print("Client disconnected.")
            break

        print(f"Client: {data}")

        data = data.encode("utf-8")
        s.sendto(data, addr)