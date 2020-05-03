from os import listdir
from os.path import isfile, join, getsize
files = [f for f in listdir("animals") if isfile(join("animals", f))]
out = open("file_sizes.txt", "w")
for f in files:
	size = getsize(join("animals", f))
	out.write(f"{f} {size}\n")
out.close()