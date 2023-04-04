#include <cs50.h>
#include <stdio.h>

// American Express uses 15-digit numbers &  start with 34 or 37
// MasterCard uses 16-digit numbers & start with 51, 52, 53, 54, or 55
// Visa uses 13- and 16-digit numbers and start with 4

// Multiply every other digit by 2, starting with the number’s second-to-last digit.
// Add those products’ digits together.
// Add the sum to the sum of the digits that weren’t multiplied by 2.
// If the total’s last digit is 0, the number is valid!

int main(void)
{   
    int i = 0

    do
    long card = get_long("Number: ");
    while (card < 0);

    while (card > 0)
    {
        card = card / 10;
        i++;
        printf("%i\n", i);
    }
    printf("%i\n", i);
}