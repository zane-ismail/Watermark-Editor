#include <cs50.h>
#include <stdio.h>

// Make sure program was run with just one command-line argument
// Make sure every character in argv[1] is a digit
// Convert argv[1] from a `string` to an `int`
// Prompt user for plaintext
// For each character in the plaintext:
// Rotate the character if it's a letter

int main(int argc, string argv[])
{
    // Iterate through each digit
    int length = 0;
    int key = 0;
    int new_key = 0;
    int new_new_key = 0;
    int multi = 1;
    const int ASCII_UPP_START = 65;
    const int ASCII_UPP_END = 90;
    const int ASCII_LOW_START = 97;
    const int ASCII_LOW_END = 122;
    const int ASCII_NUM_START = 48;
    const int ASCII_NUM_END = 57;
    string plaintext;
    for (length = 0; argv[1][length] != '\0'; length++)
    if (length > 0)
        {
         multi = (multi * 10);
        }
    // printf("%i\n", multi);
    for (length = 0; argv[1][length] != '\0'; length++)
    {
        int digit = argv[1][length];
        // Validate character as a decimal number
        if (digit >= ASCII_NUM_START && digit <= ASCII_NUM_END)
        {
            // Convert from ascii character into decimal number
            digit = digit - 48;
            digit = (digit * multi);
            key += digit;
            multi = (multi / 10);
            // printf("Key: %i\n", character);
            // printf("Length: %i\n", length);

        }
        else (printf("Usage: ./caesar key\n"));
    }
    // printf("Old Key: %i\n", key);
    //
    // Keep key number or below
    if (key > 26)
    {
        // printf("Old Key1: %i\n", key);
        new_key = (key % 26);
        // printf("New Key: %i\n", new_key);
    }
    else (new_key = key);
    // Validate only one input
    string input = argv[1];


    // Turn string input into integer
    if (argc == 2 && length != 0)
    {
        // printf("Key: %s\n", input);
        // Prompt user
        plaintext = get_string("plaintext: ");
        // Uses key to convert character
        for (length = 0; plaintext[length] != '\0'; length++)
        // Keep within a 26 letter range
        {
            // int character = (plaintext[length] - new_key);
            int character = plaintext[length];
            // printf("character: %i", character);
            // printf("newkey: %i\n", new_key);
            // printf("ch: %i", character);
            if (character <= ASCII_UPP_END && character >= ASCII_UPP_START)
            {
                character = (plaintext[length] - new_key);
                if (character < 65)
                {
                    // printf("upper: %c", character);
                    character = character + 26;
                }
            }
            else if (character <= ASCII_LOW_END && character >= ASCII_LOW_START)
            {
                character = (plaintext[length] - new_key);
                if (character < 97)
                {
                    // printf("lower: %c", character);
                    character = character + 26;
                }
            }
            else (character = character - 26);
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