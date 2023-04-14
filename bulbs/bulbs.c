#include <cs50.h>
#include <stdio.h>
#include <string.h>

void print_bulb(int bit);

int main(void)
{
    // Prompt message and establish length
    string message = get_string("Message: ");
    int length = strlen(message);
    // Iterate for length of word
    for (int i = 0; i < length; i++)
    {
        int binary[] = {0, 0, 0, 0, 0, 0, 0, 0};
        int bit = 0;
        int number = message[i];
        // Convert to binary
        do
        {
            binary[bit] = number % 2;
            number = number / 2;
            bit++;
        }
        while (number > 0);
        // Loop through eight times
        for (int j = 7; j != -1; j--)
        {
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