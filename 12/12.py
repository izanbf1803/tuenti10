def read_file_bytes(filename):
    try:
        f = open(filename, "rb")
        b = list(f.read())
        f.close()
        return b
    except Exception as ex:
        return None

def bytes_to_int(bytearr):
    v = 0
    for byte in bytearr:
        v = 256*v + byte
    return v

def file_bytes_as_int(filename):
    return bytes_to_int(read_file_bytes(filename))

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def binexp(a, n):
    res = 1
    while n > 0:
        if n & 1 == 1:
            res *= a
        a *= a
        n >>= 1
    return res

def mbinexp(a, n, m):
    a %= m
    res = 1
    while n > 0:
        if n & 1 == 1:
            res = res * a % m
        a = a * a % m
        n >>= 1
    return res

def test(n, e):
    return c1 == mbinexp(m1, e, n) and c2 == mbinexp(m2, e, n)

c1 = file_bytes_as_int("ciphered/test1.txt")
c2 = file_bytes_as_int("ciphered/test2.txt")
m1 = file_bytes_as_int("plaintexts/test1.txt")
m2 = file_bytes_as_int("plaintexts/test2.txt")

print(m1)

e_candidates = list(range(2,1000)) + [65537]
for e in e_candidates:
    x1 = abs(binexp(m1, e) - c1)
    x2 = abs(binexp(m2, e) - c2)
    g = gcd(x1, x2)
    for k in range(1,1000):
        if g % k == 0:
            n = g//k
            if test(n, e):
                print("n:", n)