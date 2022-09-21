// Modifies the volume of an audio file
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    for (int i = 0; i < HEADER_SIZE; i++)
    {
        uint8_t headers;
        fread(&headers, sizeof(headers), 1, input);
        fwrite(&headers, sizeof(headers), 1, output);
    }

    int16_t samples;
    while (fread(&samples, sizeof(samples), 1, input))
    {
        samples *= factor;
        fwrite(&samples, sizeof(samples), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}