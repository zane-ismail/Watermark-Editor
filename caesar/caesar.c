#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // Iterate through each digit
    int i;
    int key = 0;
    int new_key = 0;
    int multi = 1;
    const int ASCII_UPP_START = 65;
    const int ASCII_UPP_END = 90;
    const int ASCII_LOW_START = 97;
    const int ASCII_LOW_END = 122;
    const int ASCII_NUM_START = 48;
    const int ASCII_NUM_END = 57;
    const int ALPHABET = 26;
    string plaintext;
    // Terminate if no value is entered
    if (argc == 1)
    {
        return 1;
    }
    // Set multiplier to turn key string characters into integer of correct value
    for (i = 0; argv[1][i] != '\0'; i++)
    if (i > 0)
        {
         multi = (multi * 10);
        }
    for (i = 0; argv[1][i] != '\0'; i++)
    {
        int digit = argv[1][i];
        // Validate character as a decimal number
        if (digit >= ASCII_NUM_START && digit <= ASCII_NUM_END)
        {
            // Convert from ascii character into decimal number
            digit = digit - 48;
            digit = (digit * multi);
            key += digit;
            multi = (multi / 10);
        }
    else
    // Reject non decimal numbers
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    }
    // Keep key number 26 or below
    if (key > ALPHABET)
    {
        new_key = (key % ALPHABET);
    }
    else (new_key = key);
    // Validate only one input
    string input = argv[1];
    // Turn string input into integer
    if (argc == 2 && i != 0)
    {
        // Prompt user
        plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        // Iterate through plaintext and convert character to integer
        for (i = 0; plaintext[i] != '\0'; i++)
        // Validation so character stays within the 26 letter range
        {
            int character = plaintext[i];
            if (character <= ASCII_UPP_END && character >= ASCII_UPP_START)
            {
                character = (plaintext[i] + new_key);
                if (character > ASCII_UPP_END)
                {
                    character = character - ALPHABET;
                }
            }
            else if (character <= ASCII_LOW_END && character >= ASCII_LOW_START)
            {
                character = (plaintext[i] + new_key);
                if (character > ASCII_LOW_END)
                {
                    character = character - ALPHABET;
                }
            }
            printf("%c", character);
        }
    }
    // Return error message
    else
    {
        (printf("Usage: ./caesar key\n"));
        return 1;
    }
    printf("\n");
}