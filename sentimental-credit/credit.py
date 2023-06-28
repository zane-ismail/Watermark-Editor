# TODO
def main():
    card = get_card_number()
    card_length = get_card_length(card)
    print(card)


# Get card number
def get_card_number():
    card_number = int(input("Card number: "))
    return card_number


# Get card number length
def get_card_length(card):
    length = len(card)

    # Reject cards with less than 13 or more than 16 numbers
    if length < 13 or length > 16:
        print("INVALID")

    return length


main()
# Luhn's algorithm
# def validate_card(card, length)

