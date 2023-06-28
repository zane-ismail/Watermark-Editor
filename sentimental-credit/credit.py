# TODO
def main():
    card = get_card_number()
    card_length = get_card_length(card)
    card_type = get_card_type(card, card_length)
    if validate_card(card, card_length) == 1:
        print("INVALID")

# Get card number
def get_card_number():
    card_number = input("Card number: ")
    return card_number


# Get card number length
def get_card_length(card):
    length = len(card)

    # Reject cards with less than 13 or more than 16 numbers
    if length < 13 or length > 16:
        print("INVALID")

    return length


# Luhn's algorithm
def validate_card(card, length):
    digits = []
    sum = 0
    # Iterate to find the second to last digit and every other digit after that
    for i in range(length-2, -1, -2):
        # Multiply digit by 2
        digit = int(card[i] * 2)
        if digit < 9:
            digits.append(digit)
        # Split 2 digit numbers into single digits
        if digit > 9:
            digit = str(digit)
            digits.append(str(digit[0]))
            digits.append(str(digit[1]))

        # Add all single digits together
    for digit in digits:
        sum = sum + int(digit)

    if sum % 10 == 0:
        return 0
    else:
        return 1


# Identify card type
def get_card_type(card, length):
    digits = card[0] + card[1]
    if (length == 15) and (digits == "34" or digits == "37"):
        print("AMEX")


main()

