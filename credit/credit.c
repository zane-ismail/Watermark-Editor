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
    long i = 10;
    long digits;
    long n4;
    long m1;
    long m2 = 10;
    long m3;
    int amex = 1;
    int maca = 2;
    int visa = 3;
    int n = 0;
    int m = 0;
    runs = count - 3;
    do
    {
        i = i * 10;
        n++;
    }
    while (n < runs);

    m1 = count - 2;
    do
    {
        m2 = m2 * 10;
        m++;
    }
    while (m < m1);
    digits = card / i;
    n4 = card / m2;
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
        else if (n4 == 4)
        {
            n4 = visa;
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (count == 13)
    {
        if (n4 == 4)
        {
            n4 = visa;
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
    long divide1 = 10;
    long modular2 = 10;
    long divide2 = 1;
    long digit1 = 0;
    long digit2 = 0;
    long digit3 = 0;
    long d21 = 0;
    long d22 = 0;
    long luhns_a;
    long digit4;
    long cycle = count / 2;
    long d1;
    long d2;
    long d3;
    long d4;
    do
    {
        long a = card;
        // Find the second to last digit and every other digit after that
        a = a % modular1;
        d1 = a / divide1;
        modular1 = modular1 * 100;
        divide1 = divide1 * 100;
        // Multiply digit by 2 and add together
        d2 = (d1 * 2);
        if (d2 > 9)
        {
            d2 = (d2 / 10) + (d2 % 10);
        }
        digit1 = digit1 + d2;
        digit4 = digit1 + digit3;
        if (cycle % 10 > 0)
        {
            cycle ++;
        }
        // Find the last digit and every other digit after that
        {
        a = a % modular2;
        d3 = a / divide2;
        modular2 = modular2 * 100;
        divide2 = divide2 * 100;
        // Multiply digit by 2 and add together
        digit2 = (digit2 + d3);
        m++;
        }
    }
    while (m != cycle);
    digit3 = digit3 + d21 + d22;
    luhns_a = (digit1 + digit2);
    if (luhns_a % 10 == 0)
    {
        return 0;
    }
    else return 1;
}