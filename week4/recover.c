#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int block = 512;
uint8_t buffer[512];
int jpgnum = 0;
char filename[8];

// Function prototypes
int readwrite(FILE *img);
 
int main(int argc, char *argv[])
{
    //Check corect number of command line aguments
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    //Check for command line agument file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    else if (file != NULL)
    {
        //Establish img
        FILE *img = NULL;
        //Read card (command line agument file)
        while (fread(&buffer, sizeof(uint8_t), block, file))
        {   
            //Check for header
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                //Close img file if open
                if (img != NULL)
                {
                    fclose(img);
                    jpgnum++;
                }
                //set new img name
                sprintf(filename, "%03i.jpg", jpgnum);
                img = fopen(filename, "w");
                //Write into new img    
                fwrite(&buffer, sizeof(uint8_t), block, img);
            }
            //Check if img open
            else if (img != NULL)
            {
                //Write into image
                fwrite(&buffer, sizeof(uint8_t), block, img);
            }
        }
        fclose(file);
    }
}
