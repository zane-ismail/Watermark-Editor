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
    // printf("Length: %i\n", length);
    int j = 0;

// Take each digit
    for (letter = 0; message[letter] != '\0'; letter++)
    {
// Take first digit
            int digit_1 = message[letter] / 10;
            int digit_2 = message[letter] % 10;
            int a_1 = digit_1 % 2;
            int a = digit_1 / 2;
            int b_1 = a % 2;
            int b = a / 2;
            int c_1 = b % 2;
            int c = b / 2;
            int d_1 = c % 2;
            int d = c / 2;

            int e_1 = digit_2 % 2;
            int e = digit_2 / 2;
            int f_1 = e % 2;
            int f = e / 2;
            int g_1 = f % 2;
            int g = f / 2;
            int h_1 = g % 2;
            int h = g / 2;
            // printf("First digit: %i\n", digit_1);
            // printf("First digit: %i\n", digit_2);
            // printf("Binary 4: %i\n", a_1);
            // printf("Binary 3: %i\n", b_1);
            // printf("Binary 2: %i\n", c_1);
            // printf("Binary 1: %i\n", d_1);
            // printf("4: %i\n", a);
            // printf("3: %i\n", b);
            // printf("2: %i\n", c);
            // printf("1: %i\n", d);
            j++;
            int bits[] = {d_1, c_1, b_1, a_1, h_1, g_1, f_1, e_1};
            printf("1: %i\n", bits[0]);
            printf("2: %i\n", bits[1]);
            printf("3: %i\n", bits[2]);
            printf("4: %i\n", bits[3]);
            printf("5: %i\n", bits[4]);
            printf("6: %i\n", bits[5]);
            printf("7: %i\n", bits[6]);
            printf("8: %i\n", bits[7]);
            print_bulb(bits[0]);
            print_bulb(bits[1]);
            print_bulb(bits[2]);
            print_bulb(bits[3]);
            print_bulb(bits[4]);
            print_bulb(bits[5]);
            print_bulb(bits[6]);
            print_bulb(bits[7]);
            printf("\n");
        }
        while (j < 1);
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




        // do
        // {
        //     int divide = 1;
        //     int i = 1;
        //     do
        //     {
        //         divide = divide * 10;
        //         i++;
        //         printf("Divide: %i\n", divide);
        //     }
        //     while (i < length);



// Take last digit
//         do
//         {
//             int digit = message[letter] % 10;
//             printf("Second digit: %i\n", digit);
//             j++;
//         }
//         while (j < 1);
