#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = 0;
    char *input = argv[1];
    char *filename = malloc(8 * sizeof(char));
    int BLOCK_SIZE = 512;
    unsigned char buffer[512];
    FILE *img;

    // Accept exactly one command-line argument. If not, remind user of correct usage, and return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover [input file]");
        return 1;
    }

    // open memory card
    FILE *card = fopen(input, "r");
    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    if (card == NULL)
    {
        printf("Could not open file");
        return 1;
    }
    sprintf(filename, "%03i.jpg", count);
    img = fopen(filename, "w");
    // read 512 bytes into a buffer & repeat until end of card
    while (fread(buffer, sizeof(char), BLOCK_SIZE, card) == BLOCK_SIZE)
        // if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if first jpeg
            if (count == 0)
            {
                // Files are each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(char), BLOCK_SIZE, img);
                count++;
                printf("%i: \n", count);
            }
            // if not first jpeg
            else
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(char), BLOCK_SIZE, img);
                count++;
                printf("%i: \n", count);
            }
        }
        // if not start of new JPEG
        else
        {
            fwrite(buffer, sizeof(char), BLOCK_SIZE, img);
        }

    // Your program, if it uses malloc, must not leak any memory.
    // close any remaining files
    fclose(img);
    free(filename);
    return 0;

}