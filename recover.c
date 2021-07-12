#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }


    int count = 0;
    
    BYTE bytes[512];
    FILE *img = NULL;
    char filename[8];

    // Read every 512 bytes
    while (fread(&bytes, 512, 1, file) == 1)
    {
        // Read first three bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (!(count == 0))
            {
                fclose(img);
            }
            sprintf(filename, "%0.3i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }
        // If JPEG has been found, write to file
        if (!(count == 0))
        {
            fwrite(&bytes, 512, 1, img);
        }

    }
    fclose(file);
    fclose(img);
    return 0;
}
