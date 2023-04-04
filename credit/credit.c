#include <cs50.h>
#include <stdio.h>
#include<math.h>

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
        long first_digits = get_card_type(card, card_length);
        long card_digits = validate_card(card, card_length);
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
    long cc;
    long count = 0;
    cc = card;
    do
    {
        cc = cc / 10;
        count++;
    }
    while (cc > 0);
// Reject cards with less than 13 or more than 16 numbers
    if (count < 13 || count > 16)
    {
        printf("INVALID\n");
    }
    return count;
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

// Calculate first 2 digits for other cards and 1 digit for visa
    runs = count - 3;
    do
    {
        a = a * 10;
        i++;
    }
    while (i < runs);
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
    if (count == 15)
    {
        if (digits == 34 || digits == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (count == 16)
    {
        if (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (digits_visa == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (count == 13)
    {
        if (digits_visa == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    return 0;
}

// Luhn's algorithm
long validate_card(long card, long count)
{
    int m = 0;
    int n = 0;
    long modular1 = 100;
    long modular2 = 10;
    long divide1 = 10;
    long divide2 = 1;
    int cycle = count / 2;
    int digit1 = 0;
    int digit2 = 0;
    int digit3 = 0;
    int digit4 = 0;
    int sum;
    int int_a;
    int int_b;
    int int_c;
    int int_d;
    do
    {
        long a = card;
// Iterate to find the second to last digit and every other digit after that
        a = a % modular1;
        int_a = a / divide1;
        modular1 = modular1 * 100;
        divide1 = divide1 * 100;
// Multiply digit by 2
        int_b = (int_a * 2);
// Split 2 digit numbers into single digits
        if (int_b > 9)
        {
            int_b = (int_b / 10) + (int_b % 10);
        }
// Add all single digits together
        digit1 = digit1 + int_b;
//Rounds up for cards with an odd number of digits
        if (cycle % 10 > 0)
        {
            cycle ++;
        }
// Find the last digit and every other digit after that
        a = a % modular2;
        int_c = a / divide2;
        modular2 = modular2 * 100;
        divide2 = divide2 * 100;
        digit2 = digit2 + int_c;
        m++;
    }
    while (m != cycle);
    sum = (digit1 + digit2);
    if (sum % 10 == 0)
    {
        return 0;
    }
    return 1;
}

