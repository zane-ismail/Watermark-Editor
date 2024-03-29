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
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL)
    {
        fclose(input_file);
        printf("Could not open file\n");
        return 1;
    }

    // Read header
    // TODO #3
    fread(&header, sizeof(WAVHEADER), 1, input_file);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 1)
    {
        fclose(input_file);
        printf("Incorrect file\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output_file = fopen(output, "w");
    if (output_file == NULL)
    {
        fclose(input_file);
        fclose(output_file);
        printf("Could not open file\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output_file);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);
    int x = ftell(input_file);

    // Write reversed audio to file
    // TODO #8
    // Declare an array to store each block we read in
    unsigned char buffer[block_size];

    // Iterate through the input file audio data
    // Read in each block of auditory data starting from the very end of the input file and moving backwards
    for (fseek(input_file, 0 - block_size, SEEK_END); ftell(input_file) != x - block_size;
         fseek(input_file, 0 - (2 * block_size), SEEK_CUR))
    {
        // Simultaneously writing each block to the output file so they are written in reverse order.
        fread(buffer, block_size, 1, input_file);
        fwrite(buffer, block_size, 1, output_file);
    }
    // Close all files
    fclose(input_file);
    fclose(output_file);
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
        printf("Input is not a WAV file.\n");
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block = (header.bitsPerSample / 8) * header.numChannels;
    return block;
}