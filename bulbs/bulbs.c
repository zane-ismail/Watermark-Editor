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

// Convert to binary
    do
    {
        binary = number % 2;
        number = number / 2;
        printf("Binary: %i\n", binary);
        // printf("Number: %i\n", number);
        int bit[] = {binary};
    }
    while (number > 0);
    printf("1: %i\n", bit[0]);
    printf("2: %i\n", bit[1]);
    printf("3: %i\n", bit[2]);
    printf("4: %i\n", bit[3]);
    printf("5: %i\n", bit[4]);
    printf("6: %i\n", bit[5]);
    printf("7: %i\n", bit[6]);
    printf("8: %i\n", bit[7]);
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


