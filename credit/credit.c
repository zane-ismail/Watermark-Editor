#include <cs50.h>
#include <stdio.h>

long get_card_number(void);
long get_card_length(long card);
long get_card_type(long card, long count);
long validate_card(long card, long count);

int main(void)
{
    long card = get_card_number();
    long card_length = get_card_length(card);
    if (card_length > 12 && card_length < 17)
    {
        long card_digits = validate_card(card, card_length);
        long first_digits = get_card_type(card, card_length);
        if (card_digits == 1)
        {
            printf("INVALID\n");
        }
    }
}

// Get card number
long get_card_number(void)
{
    long card_number = get_long("Card number: ");
    return card_number;
}

// Get card number length
long get_card_length(long card)
{
    long cc = card;
    long count = 0;
    do
    {
        cc = cc / 10;
        count++;
    }
    while (cc > 0);
// Reject cards with less than 13 or more than 16 numbers
    return count;
}

// Luhn's algorithm
long validate_card(long card, long count)
{
    int n = 0;
    long modular_a = 100;
    long modular_b = 10;
    long divide1 = 10;
    long divide2 = 1;
    int cycle = count / 2;
    int sum = 0;
    int i;
    int j;
// Iterate to find the second to last digit and every other digit after that
    do
    {
        long cc = card;
        cc = cc % modular_a;
        i = cc / divide1;
        modular_a = modular_a * 100;
        divide1 = divide1 * 100;
// Multiply digit by 2
        i = (i * 2);
// Split 2 digit numbers into single digits
        if (i > 9)
        {
            i = (i / 10) + (i % 10);
        }
// Add all single digits together
        sum = sum + i;
//Rounds up for cards with an odd number of digits
        if (cycle % 10 > 0)
        {
            cycle ++;
        }
// Find the last digit and every other digit after that
        cc = cc % modular_b;
        j = cc / divide2;
        modular_b = modular_b * 100;
        divide2 = divide2 * 100;
// Add all digits together
        sum = sum + j;
        n++;
    }
// Iterates through loop until count is complete
    while (n != cycle);
// Validate modulo 10 is congruent to 0
    if (sum % 10 == 0)
    {
        return 0;
    }
    return 1;
}
// Identify card type
long get_card_type(long card, long count)
{
    long num = card;
    long a = 10;
    long b = 10;
    int runs;
    int runs_visa;
    int digits;
    int digits_visa;
    int i = 0;
    int j = 0;
// Calculate first 2 digits for Mastercard and American Express
    runs = count - 3;
    do
    {
        a = a * 10;
        i++;
    }
    while (i < runs);
// Calculate first digit for Visa
    runs_visa = count - 2;
    do
    {
        b = b * 10;
        j++;
    }
    while (j < runs_visa);
    digits = card / a;
    digits_visa = card / b;

// Validate card type
    if ((count == 15) && (digits == 34 || digits == 37))
    {
        printf("AMEX\n");
    }
    else if ((count == 16) && (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (digits_visa == 4)
    {
        printf("VISA\n");
    }
    else if ((count == 13) && (digits_visa == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}