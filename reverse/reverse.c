#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    WAVHEADER header;
    char *input = argv[1];
    char *output = argv[2];
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    FILE *input = fopen(input, "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Read header
    // TODO #3
   fread(&header, sizeof(char), 12, input);

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(header);


    // Open output file for writing
    // TODO #5
    FILE *output = fopen()

    // Write header to file
    // TODO #6

    // Use get_block_size to calculate size of block
    // TODO #7

    // Write reversed audio to file
    // TODO #8
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 87 &&  header.format[1] == 65 && header.format[2] == 86 && header.format[3] == 69)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return 0;
}