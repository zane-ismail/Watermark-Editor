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

// Get card number length and validate
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
    long runs;
    long runs_visa;
    long i = 10;
    long j = 10;
    long digits;
    long digits_visa;
    int amex = 1;
    int maca = 2;
    int visa = 3;
    int n = 0;
    int m = 0;

// Calculate first digit/s as per card type
    runs = count - 3;
    do
    {
        i = i * 10;
        n++;
    }
    while (n < runs);
    runs_visa = count - 2;
    do
    {
        j = j * 10;
        m++;
    }
    while (m < runs_visa);
    digits = card / i;
    digits_visa = card / j;

// Validate card type
    if (count == 15)
    {
        if (digits == 34 || digits == 37)
        {
            digits = amex;
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
            digits = maca;
            printf("MASTERCARD\n");
        }
        else if (digits_visa == 4)
        {
            digits_visa = visa;
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
            digits_visa = visa;
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
    long modular_a = 100;
    long modular_b = 10;
    long divide_a = 10;
    long divide_b = 1;
    long digit1 = 0;
    long digit2 = 0;
    long digit3 = 0;
    long int_b1 = 0;
    long int_b2 = 0;
    long luhns_a;
    long digit4;
    long cycle = count / 2;
    int int_a;
    int int_b;
    int int_c;
    int int_d;
    do
    {
        long a = card;
// Find the second to last digit and every other digit after that
        a = a % modular_a;
        int_a = a / divide_a;
        modular_a = modular_b * 100;
        divide_a = divide_a * 100;
// Multiply digit by 2 and add together
        int_b = (int_a * 2);
// Split 2 digit numbers into single digits
        if (int_b => 10)
        {
            int_b = (int_b / 10) + (int_b % 10);
        }
        digit1 = digit1 + int_b;
        digit4 = digit1 + digit3;
        if (cycle % 10 > 0)
        {
            cycle ++;
        }
// Find the last digit and every other digit after that
        {
        a = a % modular_b;
        int_c = a / divide_b;
        modular_b = modular_b * 100;
        divide_b = divide_b * 100;
        // Multiply digit by 2 and add together
        digit2 = (digit2 + int_c);
        m++;
        }

    }
    while (m != cycle);
    digit3 = digit3 + int_b1 + int_b2;
    luhns_a = (digit1 + digit2);
    if (luhns_a % 10 == 0)
    {
        return 0;
    }
    else return 1;
}