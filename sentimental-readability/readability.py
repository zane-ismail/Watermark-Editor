# TODO
def main():
    text = input("Text: ")
    # calculate average number of letters per 100 words
    L = 100 / count_words(text) * count_letters(text)
    # calculate average number of sentences per 100 words
    S = 100 / count_words(text) * count_sentences(text)
    # calculate grade by the Coleman-Liau formula, rounded to the nearest integer
    index = round(0.0588 * L - 0.296 * S - 15.8)
    # if index number is less than 1, output "Before Grade 1"
    if index < 1:
        print("Before Grade 1")
    # if index number is 16 or higher, output
    elif index >= 16:
        print("Grade 16+")
    # print as output "Grade X" where X is the grade level
    else:
        print(f"Grade {index}")


# Counts letters in text
def count_letters(text):
    letter_count = 0
    for word in text:
        if word.isalpha():
            letter_count = letter_count + 1
    print(letter_count)

    return letter_count


# Counts words in text
def count_words(text):
    word_count = 1
    for space in text:
        if space == " ":
            word_count = word_count + 1
    print(word_count)

    return word_count


# Counts sentences in text
def count_sentences(text):
    sentence_count = 0
    for end in text:
        if end == "." or end == "!" or end == "?":
            sentence_count = sentence_count + 1
    print(sentence_count)

    return sentence_count


main()
