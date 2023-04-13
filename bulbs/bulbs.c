#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    int letter = 0;
    string message = get_string("Message: ");
    for (letter = 0; message[letter] != '\0'; letter++)
    {
        int digit = 0;
        do
        {
            digit = message[letter] % 10;
            printf("%i\n", message[letter]);
        }
        while (digit > 0);
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
