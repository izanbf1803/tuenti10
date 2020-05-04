import codecs

unicode_let = "abcdefghijklmnopqrstuvwxyzáéíñóúü"

def only_allowed(s):
    s = s.lower()
    res = ""
    for c in s:
        if c in unicode_let:
            res += c
        else:
            res += ' '
    return res

text = None
pg17013 = codecs.open("pg17013.txt", encoding="utf-8")
text = ""
for line in pg17013:
    text += line + " "
pg17013.close()
text = only_allowed(text)
words = list(filter(lambda word: len(word) > 2, text.split())) # split text into words and ignore small words
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

inp = codecs.open("input.txt", encoding="utf-8")
out = codecs.open("output.txt", "w", encoding="utf-8")

n = int(inp.readline().strip())
for tc in range(n):
    line = inp.readline().strip()
    if line.isnumeric():
        word = word_by_rank[int(line)]
        out.write(f"Case #{tc+1}: {word} {word_freq[word]}\n")
    else:
        out.write(f"Case #{tc+1}: {word_freq[line]} #{rank[line]}\n")

inp.close()
out.close()