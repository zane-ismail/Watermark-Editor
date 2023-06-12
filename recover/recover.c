#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = 0;
    int b_count = 0;
    char *input = argv[1];
    char *filename = malloc(8 * sizeof(char));
    // read 512 bytes into a buffer
    unsigned char buffer[512];

    // Accept exactly one command-line argument. If not, remind user of correct usage, and return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover [input file]");
        return 1;
    }

    // open memory card
    FILE *f = fopen(input, "r");
    if (f == NULL)
    {
        printf("Could not open file");
        return 1;
    }


    // repeat until end of card:
    while (fread(buffer, sizeof(char), 512, f) != 0)

        // if start of new JPEG

        // if first jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            // Files are each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.
        {
            b_count++;
        }
            FILE *output;
            sprintf(filename, "%03i.jpg", count);
            FILE *img = fopen(filename, "w");
            fwrite(filename, sizeof(char), 1, img);
            count++;
        }
        else if (buffer[b_count] == 0xff && buffer[b_count + 1] == 0xd8 && buffer[b_count + 2] == 0xff && (buffer[b_count + 3] & 0xf0) == 0xe0)


            // else

            // if already found new JPEG

    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    // Your program, if it uses malloc, must not leak any memory.

    // close any remaining files
}