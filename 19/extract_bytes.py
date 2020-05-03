import sys
import random

f = open("better_farm_systems_test_image", "rb")
data = f.read()
f.close()
offset = int(sys.argv[1])
size = int(sys.argv[2])
f = open(f"bytes_{offset}_{size}_{random.random()}", "wb")
f.write(data[offset:offset+size])
f.close()