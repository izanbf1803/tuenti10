# they_see_me_rollin_they_hatin

# 1:
# E Pluribus Unum.
# In Evil we trust, because with Evil, all things are possible.
# By the tech we seek peace, but peace only under Evil, Thus always to tyrants.
# Ad astra per aspera.

# 2:
# Communication pipe broken. Run for you life.

# 3:
# A team has been dispatched, just in case keep you suicide pill reachable. Good luck.

import socket
import sys
import time
import re
import random

IP = "127.0.0.1"
PORT = 6666
BUF_SIZ = 1024*32

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((IP, PORT))

def recv():
    return sock.recv(BUF_SIZ).decode()

def precv():
    print(recv())

def send(s):
    sock.send(s.encode())

print(recv())
send("they_see_me_rollin_they_hatin\n")
print(recv())