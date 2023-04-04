#include <cs50.h>
#include <stdio.h>
#include<math.h>

long get_card_number(void);
long get_card_length(long card);
long get_first_digits(long card, long count);
long validate_card(long card, long count);

int main(void)
{
  long card = get_card_number();
  long card_length = get_card_length(card);
  long first_digits = get_first_digits(card, card_length);
  long card_digits = validate_card(card, card_length);
  if (card_digits == 1)
  {
    printf("VALID\n");
  }

}

// Validate card number
long get_card_number(void)
{
    long card_number = get_long("Card number: ");
    // printf("Card number: %ld\n", card_number);
    return card_number;
}

long get_card_length(long card)
{
    long cc;
    long count = 0;
    cc = card;
    // Check length
    do
    {
        cc = cc / 10;
        count++;
    }
    while (cc > 0);
    // Validate length
    if (count < 13 || count > 16)
    {
        printf("INVALID\n");
    }

    // printf("Card length: %ld\n", count);
    return count;
}

// American Express uses 15-digit numbers &  start with 34 or 37
// MasterCard uses 16-digit numbers & start with 51, 52, 53, 54, or 55
// Visa uses 13- and 16-digit numbers and start with 4
long get_first_digits(long card, long count)
{

    long num = card;
    long n1;
    long n2 = 10;
    long n3;
    long n4;
    long m1;
    long m2 = 10;
    long m3;
    int amex = 1;
    int maca = 2;
    int visa = 3;

    int n = 0;
    int m = 0;
    n1 = count - 3;
    do
    {
        n2 = n2 * 10;
        n++;
    }
    while (n < n1);

    m1 = count - 2;
    do
    {
        m2 = m2 * 10;
        m++;
    }
    while (m < m1);

    n3 = card / n2;
    n4 = card / m2;
    // printf("%ld\n", n3);
    // printf("%ld\n", n4);

    if (count == 15)
    {
        if (n3 == 34 || n3 == 37)
        {
            n3 = amex;
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (count == 16)
    {
        if (n3 == 51 || n3 == 52 || n3 == 53 || n3 == 54 || n3 == 55)
        {
            n3 = maca;
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

// Multiply every other digit by 2, starting with the number’s second-to-last digit.
// Add those products’ digits together.
// Add the sum to the sum of the digits that weren’t multiplied by 2.
// If the total’s last digit is 0, the number is valid!
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
        // printf("%ld\n", d1);
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
        // printf("%ld\n", d2);
        // printf("D%ld\n", d21);
        // printf("D%ld\n", d22);
        // printf("%ld\n", digit1);
        if (cycle % 10 > 0)
        {
            printf("%ld\n", cycle);
            cycle++;
        }

        // Find the last digit and every other digit after that
        {
        a = a % modular2;
        d3 = a / divide2;
        // printf("%ld\n", d3);
        modular2 = modular2 * 100;
        divide2 = divide2 * 100;

        // Multiply digit by 2 and add together
        digit2 = (digit2 + d3);
        // printf("%ld\n", digit2);
        m++;
    }
    while (m != cycle);


    digit3 = digit3 + d21 + d22;
    luhns_a = (digit1 + digit2);
    printf("%ld\n", luhns_a);
    if (luhns_a % 10 == 0)
    {
        return 0;
    }
    else return 0;
}