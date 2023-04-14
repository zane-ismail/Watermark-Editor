#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS = 8;
void print_bulb(int bit);

int main(void)
{
// TODO
    int sum;
    string message = get_string("Message: ");
    int bit[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int number = 72;
    int i = 0;
// Convert to binary
    do
    {
        bit[i] = number % 2;
        number = number / 2;
        i++;
    }
    while (number > 0);
// Print bulbs
    for (int j = 7; j != -1; j--)
    {
        print_bulb(bit[j]);
    }
    printf("\n");
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


