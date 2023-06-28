# TODO
def main():
    card = get_card_number()
    card_length = get_card_length(card)
    validate_card(card, card_length)
    # print(card_length)


# Get card number
def get_card_number():
    card_number = int(input("Card number: "))
    return card_number


# Get card number length
def get_card_length(card):
    length = len(str(card))

    # Reject cards with less than 13 or more than 16 numbers
    if length < 13 or length > 16:
        print("INVALID")

    return length


# Luhn's algorithm
def validate_card(card, length):
    card = str(card)
    print(card)
    # Iterate to find the second to last digit and every other digit after that
    for i in range(0, length, 2):
        for digit in card:
            print(digit)
            sum = digit * 2

    return


main()

