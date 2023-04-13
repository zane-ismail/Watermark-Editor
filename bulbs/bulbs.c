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

// Get length
    int length = strlen(message);
    printf("%i\n", length);

// Take each digit
    for (letter = 0; message[letter] != '\0'; letter++)
    {
        int j = 0;


// Take first digit
        do
        {
            message[letter] = message[letter] / 10;
            int a = message[letter] % 2;
            int b = a % 2;
            int c = b % 2;
            int d = c % 2;
            printf("%i\n", message[letter]);
            // printf("%i\n", a);
            // printf("%i\n", b);
            // printf("%i\n", c);
            // printf("%i\n", d);
            j++;
        }
        while (j < length);
// Take last digit
        do
        {
            int digit = message[letter] % 10;
            printf("%i\n", digit);
            j++;
        }
        while (j < 1);
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



// // Count number of letters
//     int i = 0;
//     do
//     {
//         message[letter] = message[letter] / 10;
//         i++;
//     }
//     while (message[letter] > 0);
//     printf("%i\n", i);
//     printf("%i\n", message[letter]);