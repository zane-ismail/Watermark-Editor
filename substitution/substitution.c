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
            key[i] = num;
        }
    if (i != 26)
    {
        printf("Key must contain 26 characters.\n");
    }
        // printf("%i\n", key[0]);
        // printf("%i\n", key[1]);
        // printf("%i\n", key[2]);
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
                if (key[i] >= ASCII_LOW_START)
                {
                    character = (character - 32);
                    printf("!");
                }
                else
                {
                    printf(",");
                }
            }
            else if (character >= ASCII_LOW_START && character <= ASCII_LOW_END)
            {
                character = (plaintext[i] - ASCII_LOW_START);
                character = key[character];
                if (key[character] <= ASCII_UPP_END)
                {
                    printf(".%i.", key[character]);
                    character = (character + 32);
                    // printf(".%i.", key[i]);
                }
                else
                {
                    printf(".");
                }
            }
            else
            {
                printf("OTHER");
            }
            printf("%c", character);
        }
    printf("\n");
}
