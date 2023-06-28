# TODO
def main():
    card = get_card_number()
    card_length = get_card_length(card)
    if validate_card(card, card_length) == 0:
        print("INVALID")
        return
    card_type = get_card_type(card, card_length)


# Get card number
def get_card_number():
    try:
        card_number = int(input("Card number: "))
        card_number = str(card_number)
    except:
        get_card_number()

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
        digit = int(card[i])
        digit = digit * 2
        if digit < 9:
            digits.append(digit)
    # Iterate to find every other digit
    for j in range(0, length, 2):
        digits.append(int(card[j]))

        # Add all single digits together
    print(digits)
    for digit in digits:
        sum = sum + int(digit)

    if sum % 10 == 0:
        print(sum)
        return 1
    else:
        print(sum)
        return 0


# Identify card type
def get_card_type(card, length):
    visa_digit = card[0]
    digits = card[0] + card[1]
    if length == 15 and digits == "34" or digits == "37":
        print("AMEX")

    elif length == 16 and digits == "51" or digits == "52" or digits == "53" or digits == "54" or digits == "55":
        print("MASTERCARD")

    elif visa_digit == "4":
        print("VISA")

    elif length == 13 and visa_digit == "4":
        print("VISA")

    else:
        print("INVALID")


main()

