import socket
import sys
import time
import re
import random

IP = "52.49.91.111"
PORT = 2092
BUF_SIZ = 1024*32

LEARN_RE = re.compile(r"\{servers: (\[[\d,]+\]), secret_owner: ([\d]+)\}")
ID_RE = re.compile(r"(\{[\d]+,[\d]+\})")

def parse_learn(s):
    res = LEARN_RE.search(s)
    d = dict()
    d["servers"] = res.group(1)
    d["secret_owner"] = res.group(2)
    return d

def parse_promise(s):
    res = ID_RE.search(s)
    return res.group(1)

def timestamp():
    return "{:.4f}".format(time.time()).replace(".", "")

def send(msg):
    sock.send(msg.encode())

def recv():
    return sock.recv(BUF_SIZ).decode()

def format_list(l):
    s = str(l)
    return s.replace(" ", "")


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((IP, PORT))

started = False
mem = dict()

prep_id = f"{{{timestamp()},9}}"
prepared = False
promised = set()

while True:
    # send("ACCEPT {id: {1,2}, value: {servers: [1, 2, 3, 4, 5, 6, 7, 8], secret_owner: 5}} -> 3")
    msg = recv()

    print(msg)

    # continue

    if started:
        lines = msg.split('\n')
        ops = []
        for line in lines:
            if " -> " in line:
                autor, ins = line.split(" -> ")
                autor = autor.split(":")[1][1:]
                op = None
                if "LEARN" in ins:
                    op = (autor, "LEARN", parse_learn(ins))
                if "PROMISE" in ins:
                    op = (autor, "PROMISE", parse_promise(ins))
                if op != None:
                    ops.append(op)

        round_end = "(ROUND FINISHED)" in msg
        if round_end:
            for op in ops:
                if op[1] == "LEARN":
                    mem = op[2]

            prep_id = f"{{{timestamp()},9}}"
            prepared = False
            promised = set()

        for op in ops:
            if prepared and op[1] == "PROMISE" and op[2] == prep_id:
                promised.add(int(op[0]))

        if "servers" in mem:
            secret_owner = int(mem["secret_owner"])
            servers = eval(mem["servers"])
            to_kill = None
            if len(servers) >= 3:
                candidates = list(servers)
                candidates.remove(9)
                # candidates.remove(secret_owner)
                to_kill = random.choice(candidates)
            if prepared:
                # pass
                if len(promised) >= (len(servers)+1)/2:
                    for serv in promised:

                        new_servers = [9] + list(promised)
                        new_servers.sort()
                        if to_kill != None:
                            new_servers.remove(to_kill)
                        new_servers = format_list(new_servers)
                        to_send = f'ACCEPT {{id: {prep_id}, value: {{servers: {new_servers}, secret_owner: {secret_owner}}}}} -> {serv}\n'
                        print("\t\t"+to_send)
                        send(to_send)


                        #### Only promised
                        # new_servers = [9] + list(promised)
                        # new_servers.sort()
                        # if serv in new_servers and int(serv) != secret_owner:
                        #     new_servers.remove(serv)
                        # new_servers = format_list(new_servers)
                        # print("\t\t"+f'ACCEPT {{id: {prep_id}, value: {{servers: {new_servers}, secret_owner: {secret_owner}}}}} -> {serv}\n')
                        # send(f'ACCEPT {{id: {prep_id}, value: {{servers: {new_servers}, secret_owner: {secret_owner}}}}} -> {serv}\n')

                        #### Just wait
                        # send(f'ACCEPT {{id: {prep_id}, value: {{servers: {mem["servers"]}, secret_owner: {secret_owner}}}}} -> {serv}\n')

                    prep_id = f"{{{timestamp()},9}}"
                    prepared = False
                    promised = set()
            else:
                prepared = True
                for serv in servers:
                    if serv != 9:
                        to_send = f'PREPARE {prep_id} -> {serv}\n'
                        print("\t\t"+to_send)
                        send(to_send)

    else:
        started = "AUTOJOIN CLUSTER ENABLED" in msg


    

    # print("PROM", promised)


    print("---------------")
    print("MEM:", mem)
    # send(f"PREPARE {{{timestamp()},9}} -> 4")

sock.close()