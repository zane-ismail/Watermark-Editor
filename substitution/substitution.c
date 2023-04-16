#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    const int ALPHABET = 26;
    const int ASCII_UPP_START = 65;
    const int ASCII_UPP_END = 90;
    const int ASCII_LOW_START = 97;
    const int ASCII_LOW_END = 122;
    int num;
    int key[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    string plaintext;
    // Terminate if wrong value is entered
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Iterate through argv to add each value to an array
    for (i = 0; argv[1][i] != '\0'; i++)
    {
        // Validate alphabetical uppercase characters only
        num = argv[1][i];
        if (num >= ASCII_UPP_START && num <= ASCII_UPP_END)
        {
            key[i] = num;
        }
        // Validate alphabetical lowercase characters only
        else if (num >= ASCII_LOW_START && num <= ASCII_LOW_END)
        {
            key[i] = num;
        }
        else
        {
            return 1;
        }
    }
    // Validate correct number of characters
    if (i != ALPHABET)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check for duplicate characters
    for (i = 0; i < ALPHABET; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (key[j] == key[i])
            {
                return 1;
            }
        }
    }
    // Prompt user for plaintext
    plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (i = 0; plaintext[i] != '\0'; i++)
    {
        int character = plaintext[i];
        // Keep uppercase characters in uppercase
        if (character >= ASCII_UPP_START && character <= ASCII_UPP_END)
        {
            character = (plaintext[i] - ASCII_UPP_START);
            character = key[character];
            if (character >= ASCII_LOW_START)
            {
                character = (character - 32);
            }
        }
        // Keep lowercase characters in lowercase
        else if (character >= ASCII_LOW_START && character <= ASCII_LOW_END)
        {
            character = (plaintext[i] - ASCII_LOW_START);
            character = key[character];
            if (character <= ASCII_UPP_END)
            {
                character = (character + 32);
            }
        }
        printf("%c", character);
    }
    printf("\n");
}