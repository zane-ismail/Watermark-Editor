#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS = 8;
void print_bulb(int bit);

int main(void)
{
    // TODO
    int letter = 0;
    int sum;
    int power = 1;
    string message = get_string("Message: ");
    int number = 21;
    do
    {
        power = (power * 2);
        printf("Power: %i\n", power);
    }
    while (power < number);
    printf("%i\n", number);
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


