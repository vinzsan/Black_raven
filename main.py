import socket, struct

HOST, PORT = "vortex.labs.overthewire.org", 5842
with socket.create_connection((HOST, PORT)) as s:
    data = s.recv(16, socket.MSG_WAITALL)   # baca 16 byte
    nums = struct.unpack("<4I", data)       # 4 unsigned int, little endian
    print("Received:", nums)
    total = sum(nums) & 0xFFFFFFFF          # wrap 32-bit
    s.sendall(struct.pack("<I", total))     # kirim balik 4-byte little endian
    print(s.recv(4096).decode())
