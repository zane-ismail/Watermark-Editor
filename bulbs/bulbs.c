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
    int binary[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int bit = 0;
    int length = strlen(message);
// Convert to binary
    for (int i = 0; i < length; i++)
    {
        int number = message[i];
        printf("%i\n", message[i]);
        do
        {
            binary[bit] = number % 2;
            number = number / 2;
            bit++;
        }
        while (number > 0);
        for (int j = 7; j != -1; j--)
        {
            // printf("%i\n", binary[j]);
            print_bulb(binary[j]);
        }
        printf("\n");
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


