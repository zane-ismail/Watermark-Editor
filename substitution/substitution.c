#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    const int ALPHABET = 26;
    const int ASCII_NUM_START = 48;
    const int ASCII_NUM_END = 57;
    const int ASCII_UPP_START = 65;
    const int ASCII_UPP_END = 90;
    const int ASCII_LOW_START = 97;
    const int ASCII_LOW_END = 122;
    int num;
    int letters[26];
    int key[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    string plaintext;
    // Terminate if wrong value is entered
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Validate correct number of characters
    // Iterate through argv to add each value to an array
     for (i = 0; argv[1][i] != '\0'; i++)
        {
            num = argv[1][i];
            if (num >= ASCII_UPP_START && num <= ASCII_UPP_END)
            {
                key[i] = num;
            }
            else if (num >= ASCII_LOW_START && num <= ASCII_LOW_END)
            {
                key[i] = num;
                // printf("%i", i);
            }
            else
            {
                return 1;
            }
        }

    if (i != ALPHABET)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check for duplicates
    for (i = 0; i < ALPHABET; i++)
    {
        if letters[i] == int key[i]
        {
            printf("DUPLICATE!");
        }
    }

    // Prompt user for plaintext
        plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        for (i = 0; plaintext[i] != '\0'; i++)
        {
            int character = plaintext[i];
            // Validation for input characters
            if (character >= ASCII_UPP_START && character <= ASCII_UPP_END)
            {
                character = (plaintext[i] - ASCII_UPP_START);
                character = key[character];
                if (character >= ASCII_LOW_START)
                {
                    character = (character - 32);
                    // printf("!");
                }
                else
                {
                    // printf(",");
                }
            }
            else if (character >= ASCII_LOW_START && character <= ASCII_LOW_END)
            {
                character = (plaintext[i] - ASCII_LOW_START);
                character = key[character];
                if (character <= ASCII_UPP_END)
                {
                    // printf(".%i.", key[character]);
                    character = (character + 32);
                    // printf(".%i.", key[i]);
                }
                else
                {
                    // printf(".");
                }
            }

            printf("%c", character);
        }
    printf("\n");
}
