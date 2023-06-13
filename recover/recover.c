#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = 0;
    int BLOCK_SIZE = 512;
    char *input = argv[1];
    char *filename = malloc(8 * sizeof(char));
    unsigned char buffer[512];
    FILE *img = NULL;

    // Accept exactly one command-line argument. If not, remind user of correct usage, and return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover [input file]");
        return 1;
    }

    // open memory card
    FILE *card = fopen(input, "r");
    // If the forensic image cannot be opened for reading, inform the user and return 1.
    if (card == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    // read 512 bytes into a buffer & repeat until end of card
    while (fread(buffer, sizeof(char), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Files are named ###.jpg, (a 3-digit number), starting with 000 and counting up.
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;

        }
        // if not start of new JPEG
        if (img != NULL)
        {
            fclose(img);
            fwrite(buffer, sizeof(char), BLOCK_SIZE, img);
        }
    }

    // If used malloc, must not leak any memory.
    free(filename);

    // close any remaining files
    fclose(img);
    fclose(card);

    return 0;
}