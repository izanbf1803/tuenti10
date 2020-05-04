import socket, sys

IP = "52.49.91.111"
PORT = 2003
BUF_SIZ = 1024

dir_x = [+1, +2, +2, +1, -1, -2, -2, -1]
dir_y = [-2, -1, +1, +2, +2, +1, -1, -2]

def dir_to_str(dx, dy):
    res = ""
    if dy < 0:
        res += str(-dy) + "u"
    else:
        res += str(dy) + "d"
    if dx < 0:
        res += str(-dx) + "l"
    else:
        res += str(dx) + "r"
    return res

def recv(s):
    lines = s.recv(BUF_SIZ).decode().split('\n')
    grid = []
    for line in lines:
        if len(line) == 0 or line[0] == '-':
            break
        grid.append(line)
    return grid

def send(s, msg):
    s.send(msg.encode())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))

SIZE = 400 # Just make it big and start at center
visited = [[False for _ in range(SIZE)] for _ in range(SIZE)]

def dfs(px, py):
    visited[py][px] = True

    grid = recv(s)

    h = len(grid)
    w = len(grid[0])

    kx, ky = -1, -1
    for y in range(h):
        for x in range(w):
            if grid[y][x] == 'K':
                kx, ky = x, y

    for i in range(8):
        dx = dir_x[i]
        dy = dir_y[i]
        if grid[ky+dy][kx+dx] == 'P': # solved :)
            send(s, dir_to_str(dx, dy))
            print(s.recv(BUF_SIZ)) # Print key
            sys.exit(0)
        elif grid[ky+dy][kx+dx] == '.':
            px2 = px+dx
            py2 = py+dy
            if not visited[py2][px2]:
                send(s, dir_to_str(dx, dy))
                dfs(px2, py2)
                send(s, dir_to_str(-dx, -dy))
                recv(s)

dfs(SIZE//2, SIZE//2)

s.close()