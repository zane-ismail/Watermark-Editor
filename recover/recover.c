#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = - 1;
    int b_count = 0;
    char *input = argv[1];
    char *filename = malloc(8 * sizeof(char));
    int BLOCK_SIZE = 512;
    unsigned char buffer[BLOCK_SIZE];
    FILE *img;


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

    // read 512 bytes into a buffer & repeat until end of card
    while (fread(buffer, sizeof(char), BLOCK_SIZE, f) == BLOCK_SIZE)
        // if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            count++;
            printf("%i\n", count);
            // Files are each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            // if first jpeg
            if (count == 0)
            {
                fwrite(buffer, sizeof(char), (BLOCK_SIZE), img);
            }
            else
            {
                // close any remaining files
                fclose(img);
            }
        }
        else
        {
            fwrite(buffer, sizeof(char), (BLOCK_SIZE), img);
        }

    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    // Your program, if it uses malloc, must not leak any memory.

}