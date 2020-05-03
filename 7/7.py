import codecs

m = {} # Letter mapping
m["."] = "E"
m["y"] = "T"
m["d"] = "H"
m["r"] = "O"
m["u"] = "F"
m["a"] = "A"
m["b"] = "N"
m["e"] = "D"
m["c"] = "I"
m["p"] = "R"
m["k"] = "V"
m["n"] = "L"
m["x"] = "B"
m["o"] = "S"
m["m"] = "M"
m["f"] = "Y"
m["l"] = "P"
m["j"] = "C"
m["t"] = "K"
m[","] = "W"
m["i"] = "G"
m["g"] = "U"
m["h"] = "J"
m[";"] = "Z"
m["'"] = "Q"
m["v"] = "."
m["w"] = ","
m["q"] = "X"
m["-"] = "'"
m["z"] = "/"
m["s"] = ";"

file = codecs.open("testInput.txt", encoding="utf-8")
n = int(file.readline().strip())
for i in range(n):
    line = file.readline()
    dec = ""
    for c in line[:-1]:
        # print(c, c in m, -1 if c not in m else m[c])
        if c in m:
            dec += m[c].lower()
        else:
            dec += c.upper()
    print(f"Case #{i+1}: {dec}")