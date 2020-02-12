#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    const int DFAT = 512;
    // check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // open memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }

    // create buffer to read 512 bytes at a time
    unsigned char buffer[DFAT];
    // pointer to outfile
    FILE *output = NULL;
    // create image filenames;
    char image[8];
    // counter to keep track of images
    int n = 0;

    // Repeat until end of card
    while (fread(buffer, DFAT, 1, card) == 1)
    {
        //if start of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 || buffer[3] <= 0xef))
        {
            // if not first jpeg close file first
            if (n > 0)
            {
                fclose(output);
            }
            //make nth image name and open file
            sprintf(image, "%03i.jpg", n);
            output = fopen(image, "w");
            n++;
        }
        // write to file if open and exists
        if (output != NULL)
        {
            fwrite(buffer, DFAT, 1, output);
        }

    }

    // close remaining files
    fclose(output);
    fclose(card);
return 0;
}