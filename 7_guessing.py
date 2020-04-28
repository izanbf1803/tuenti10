import codecs

allowed = "abcdefghijklmnopqrstuvwxyz0123456789.,;-'"

def only_allowed(s):
    s = s.lower()
    res = ""
    for c in s:
        if c in allowed:
            res += c
        else:
            res += ' '
    return res

file = codecs.open("testInput.txt", encoding="utf-8")
text = ""
for line in file:
    text += line
file.close()

# I reused the code from the problem 3 cause
# i thought freq. analysis would be useful,
# Just by gessing checking most common english words,
# and iteratively checking new formed words by hand,
# it is ordered as i guessed it:
text = text.replace(".", "E")
text = text.replace("y", "T")
text = text.replace("d", "H")
text = text.replace("r", "O")
text = text.replace("u", "F")
text = text.replace("a", "A")
text = text.replace("b", "N")
text = text.replace("e", "D")
text = text.replace("c", "I")
text = text.replace("p", "R")
text = text.replace("k", "V")
text = text.replace("n", "L")
text = text.replace("x", "B")
text = text.replace("o", "S")
text = text.replace("m", "M")
text = text.replace("m", "M")
text = text.replace("f", "Y")
text = text.replace("l", "P")
text = text.replace("j", "C")
text = text.replace("t", "K")
text = text.replace(",", "W")
text = text.replace("i", "G")
text = text.replace("g", "U")
text = text.replace("h", "J")
text = text.replace(";", "Z")
text = text.replace("'", "Q")

text = text.replace("v", ".")
text = text.replace("w", ",")

print(text)

text = only_allowed(text)

words = list(filter(lambda word: len(word) > 1, text.split())) # split text into words and ignore small words
word_freq = {}
for word in words:
    if word in word_freq:
        word_freq[word] += 1
    else:
        word_freq[word] = 1
unique_words = []
for word in word_freq:
    unique_words.append(word)
unique_words.sort(key=lambda word: (-word_freq[word], word)) # sort by greatest freq, smallest word
rank = {}
word_by_rank = {}

for i in range(len(unique_words)):
    word = unique_words[i]
    rank[word] = i+1
    word_by_rank[i+1] = word

for w in unique_words:
    if w.upper() != w:
        print(w, word_freq[w])