// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // this header is always exactly 44 bytes long/ volume.c already defines a variable for you called HEADER_SIZE, equal to the number of bytes in the header.
    uint8_t header[HEADER_SIZE];

    // Your program should first read the header from the input file and write the header to the output file.
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    // assume that the WAV file will use 16-bit signed values as samples.
    int16_t buffer;

    // read the rest of the data from the WAV file, one 16-bit (2-byte) sample at a time.
    while (fread(&buffer, 2, 1, input))
    {
        // multiply each sample by the factor and write the new sample to the output file.
        buffer *= factor;

        fwrite(&buffer, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
