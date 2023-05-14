#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    // The files you generate should each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.
    // Your program, if it uses malloc, must not leak any memory.

    // Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
    // If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover [input file]");
        return 1;
    }
    char *input = argv[1];

    // open memory card
    char *buffer;
    fread(buffer, 512, 1, input)
    // repeat until end  of card:


        // read 512 bytes into a buffer

        // if start of new JPEG

            // if first JPEG

            // else

        // else
            // if already found new JPEG

    // close any remaining files
}