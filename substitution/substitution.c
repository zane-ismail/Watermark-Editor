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
    int factor = 1;
    int key = 0;
    int i;
    string plaintext;
    // Terminate if wrong value is entered
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}