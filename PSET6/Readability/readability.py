txt = input("Text: ")
n_letters = 0
n_words = 1
n_sentences = 0
for i in txt:
    if (i == ' '):
        n_words += 1
    elif (i == '.' or i == '?' or i == '!'):
        n_sentences += 1
    if (i.isalpha()):
        n_letters += 1

L = 100 * n_letters / n_words
S = 100 * n_sentences / n_words
readablity = round(0.0588 * L - 0.296 * S - 15.8)

if readablity >= 16:
    print("Grade 16+")
elif readablity < 1:
    print("Before Grade 1")
else:
    print(f"Grade {readablity}")
