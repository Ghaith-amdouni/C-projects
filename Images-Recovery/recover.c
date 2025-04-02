#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 512
#define FILE_NAME_SIZE 8

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    // Open the input file
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    uint8_t buffer[BLOCK_SIZE];
    int jpeg_count = 0;
    char filename[FILE_NAME_SIZE];
    FILE *output = NULL;
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", jpeg_count++);
            output = fopen(filename, "wb");
            if (output == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(input);
                return 3;
            }
        }
        // If a JPEG file is open, write the block to it
        if (output != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, output);
        }
    }
    // Close any remaining open files
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);
    return 0;

}
