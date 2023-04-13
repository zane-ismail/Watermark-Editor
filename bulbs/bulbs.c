#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS = 8;
void print_bulb(int bit);

int main(void)
{
    // TODO
    int letter = 0;
    string message = get_string("Message: ");

// Get length
    int length = strlen(message);
    printf("Length: %i\n", length);

// Take each digit
    for (letter = 0; message[letter] != '\0'; letter++)
    {
        int j = 0;


// Take first digit
        do
        {
            int divide = 1;
            int i = 1;
            do
            {
                divide = divide * 10;
                i++;
            }
            while (i < length);
            int digit = message[letter] / divide;
            int a_1 = digit % 2;
            int a = digit / 2;
            int b_1 = a % 2;
            int b = a / 2;
            int c_1 = b % 2;
            int c = b / 2;
            int d_1 = c % 2;
            int d = c / 2;
            printf("First digit: %i\n", digit);
            printf("Binary 4: %i\n", a_1);
            printf("Binary 3: %i\n", b_1);
            printf("Binary 2: %i\n", c_1);
            printf("Binary 1: %i\n", d_1);
            printf("4: %i\n", a);
            printf("3: %i\n", b);
            printf("2: %i\n", c);
            printf(": %i\n", d);
            j++;
            divide = divide * 10;
        }
        while (j < length);
// Take last digit
//         do
//         {
//             int digit = message[letter] % 10;
//             printf("Second digit: %i\n", digit);
//             j++;
//         }
//         while (j < 1);
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