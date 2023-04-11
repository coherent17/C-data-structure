# pip install RandomWords
from random_words import RandomWords
rw = RandomWords()
words_short = rw.random_words(count=1000)

with open('words_short.txt', 'w') as file:
    for word in words_short :
        file.write(word + '\n')

words_long = rw.random_words(count=5449)

with open('words_long.txt', 'w') as file:
    for word in words_long  :
        file.write(word + '\n')