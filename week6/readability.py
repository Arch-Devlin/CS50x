# Librarys
import sys


def main():
    # Get input text
    text = input("Text: ")
    # count letters
    letters = compute_letters(text)
    print(f"{letters} Letter(s)")
    # count spaces + 1
    words = compute_words(text)
    print(f"{words} Letter(s)")
    # Count sentences
    sentences = compute_sentences(text)
    print(f"{sentences} Letter(s)")
    # calculate average number of letters per 100 words in the text (L)
    L = 100 * (letters / words)
    print(f"{L} Letter(s)")
    # calculate the average number of sentences per 100 words (S)
    S = 100 * (sentences / words)
    print(f"{S} Letter(s)")
    # calculate Coleman-Liau index
    index = ((0.0588 * L) - (0.296 * S) - (15.8))
    print(f"{index} Letter(s)")
    # round Coleman-Liau index
    CLI = round(index)
    print(f"{CLI} Letter(s)")

    # Final outcome
    if CLI < 1:
        print("Before Grade 1")
    elif CLI >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {CLI}")


def compute_letters(texts):
    letter = 0
    for i in range(len(texts)):
        if texts[i].isalpha():
            letter += 1
    return letter


def compute_words(texts):
    word = 1
    for i in range(len(texts)):
        if texts[i].isspace():
            word += 1
    return word


def compute_sentences(texts):
    sentence = 0
    for i in range(len(texts)):
        if texts[i] == '.' or texts[i] == '!' or texts[i] == '?':
            sentence += 1
    return sentence


main()
