#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
        printf("Usage: ./recover card.raw\n");
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        return 2;
        printf("Could not open %s.\n", argv[1]);
    }

    int fcount = 0;
    BYTE buffer[512];
    FILE *outfile = NULL;
    while (fread(&buffer, sizeof(buffer), 1, infile))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 224 && buffer[3] < 240)
        {
            char *file_name = (char *)malloc(8 * sizeof(char));
            sprintf(file_name, "%.3i.jpg", fcount++);
            if (fcount > 1)
            {
                fclose(outfile);
            }
            outfile = fopen(file_name, "w");
            if (outfile == NULL)
            {
                return 3;
            }
            free(file_name);
        }
        if (outfile != NULL)
        {
            fwrite(&buffer, sizeof(buffer), 1, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}