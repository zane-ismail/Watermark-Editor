#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS = 8;
void print_bulb(int bit);

int main(void)
{
    // TODO

    int sum;
    // int binary;
    string message = get_string("Message: ");
    int number = message;
    int bit[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
// Convert to binary
    do
    {
        bit[i] = number % 2;
        number = number / 2;
        // printf("Binary: %i\n", bit[i]);
        // printf("Number: %i\n", number);
        // printf("1: %i\n", bit[0]);
        // print_bulb(bit[i]);
        i++;
    }
    while (number > 0);
    for (int j = 7; j != -1; j--)
    {
        print_bulb(bit[j]);
    }
    printf("\n");

    // printf("2: %i\n", bit[7]);
    // printf("2: %i\n", bit[6]);
    // printf("2: %i\n", bit[5]);
    // printf("2: %i\n", bit[4]);
    // printf("2: %i\n", bit[3]);
    // printf("2: %i\n", bit[2]);
    // printf("2: %i\n", bit[1]);
    // printf("2: %i\n", bit[0]);


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


