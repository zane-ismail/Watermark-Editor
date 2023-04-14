#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS = 8;
void print_bulb(int bit);

int main(void)
{
    // TODO

    int sum;
    int binary;
    string message = get_string("Message: ");
    int number = 72;
    int bit[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;

// Convert to binary
    do
    {
        bit[i] = number % 2;
        number = number / 2;
        printf("Binary: %i\n", binary);
        // printf("Number: %i\n", number);
        // printf("1: %i\n", bit[0]);
        i++;
    }
    while (number > 0);
    print_bulb(binary);
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


