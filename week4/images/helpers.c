#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //calculating new RGB
            float grey3 = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            float greyf = grey3 / 3;
            int grey = round(greyf);

            //Setting new RGB
            image[h][w].rgbtBlue = grey;
            image[h][w].rgbtGreen = grey;
            image[h][w].rgbtRed = grey;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Settup RGB array
    RGBTRIPLE tmp[height][width];

    //going through each pixl
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            //seting tmp pixl aray
            tmp[h][w] = image[h][w];
            //reflecting
            image[h][w] = image[h][width - (w + 1)];
            image[h][width - (w + 1)] = tmp[h][w];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Setup variables
    float avgB[height][width];
    float avgG[height][width];
    float avgR[height][width];

    int B = 0;
    int G = 0;
    int R = 0;

    float pxl[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            avgB[h][w] = 0;
            avgG[h][w] = 0;
            avgR[h][w] = 0;

            int y = 0;
            int x = 0;

            int yy = 0;
            int xx = 0;

            pxl[h][w] = 0;
            // Check pixl position
            if (h > 0)
            {
                y = -1;
            }
            else
            {
                y = 0;
            }

            if (h == height - 1)
            {
                yy = 1;
            }
            else
            {
                yy = 2;
            }

            if (w > 0)
            {
                x = -1;
            }
            else
            {
                x = 0;
            }

            if (w == width - 1)
            {
                xx = 1;
            }
            else
            {
                xx = 2;
            }
            // Add adjacent pixles
            for (int i = y; i < yy; i++)
            {
                for (int j = x; j < xx; j++)
                {
                    avgB[h][w] = avgB[h][w] + image[h + i][w + j].rgbtBlue;
                    avgG[h][w] = avgG[h][w] + image[h + i][w + j].rgbtGreen;
                    avgR[h][w] = avgR[h][w] + image[h + i][w + j].rgbtRed;

                    pxl[h][w]++;
                }
            }
        }
    }
    //Blur
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //new RGB = avg / 3
            B = round(avgB[h][w] / pxl[h][w]);
            G = round(avgG[h][w] / pxl[h][w]);
            R = round(avgR[h][w] / pxl[h][w]);

            // Setting new RGB
            image[h][w].rgbtBlue = B;
            image[h][w].rgbtGreen = G;
            image[h][w].rgbtRed = R;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Setup variables
    float gxB[height][width];
    float gxG[height][width];
    float gxR[height][width];

    float gyB[height][width];
    float gyG[height][width];
    float gyR[height][width];

    float Bs = 0;
    float Gs = 0;
    float Rs = 0;

    int B = 0;
    int G = 0;
    int R = 0;


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //establishing variables
            gxB[h][w] = 0;
            gxG[h][w] = 0;
            gxR[h][w] = 0;

            gyB[h][w] = 0;
            gyG[h][w] = 0;
            gyR[h][w] = 0;

            float factorx = 0;
            float factory = 0;

            int y = 0;
            int x = 0;

            int yy = 0;
            int xx = 0;


            // Check pixl position
            if (h == 0)
            {
                y = 0;
            }
            else
            {
                y = -1;
            }

            if (h == height - 1)
            {
                yy = 1;
            }
            else
            {
                yy = 2;
            }

            if (w > 0)
            {
                x = -1;
            }
            else
            {
                x = 0;
            }

            if (w == width - 1)
            {
                xx = 1;
            }
            else
            {
                xx = 2;
            }
            // include adjacent pixles
            for (int i = y; i < yy; i++)
            {
                for (int j = x; j < xx; j++)
                {
                    //setting the Gx kernel
                    if (i == 0)
                    {
                        factorx = j + j;
                    }
                    else
                    {
                        factorx = j;
                    }
                    //setting the Gy kernel
                    if (j == 0)
                    {
                        factory = i + i;
                    }
                    else
                    {
                        factory = i;
                    }
                    
                    //calculate Gx
                    gxB[h][w] = gxB[h][w] + (image[h + i][w + j].rgbtBlue * factorx);
                    gxG[h][w] = gxG[h][w] + (image[h + i][w + j].rgbtGreen * factorx);
                    gxR[h][w] = gxR[h][w] + (image[h + i][w + j].rgbtRed * factorx);
                    //calculate Gy
                    gyB[h][w] = gyB[h][w] + (image[h + i][w + j].rgbtBlue * factory);
                    gyG[h][w] = gyG[h][w] + (image[h + i][w + j].rgbtGreen * factory);
                    gyR[h][w] = gyR[h][w] + (image[h + i][w + j].rgbtRed * factory);
                }
            }
        }
    }
    //output
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Gx^2 + Gy^2
            Bs = (gxB[h][w] * gxB[h][w]) + (gyB[h][w] * gyB[h][w]);
            Gs = (gxG[h][w] * gxG[h][w]) + (gyG[h][w] * gyG[h][w]);
            Rs = (gxR[h][w] * gxR[h][w]) + (gyR[h][w] * gyR[h][w]);

            //square root of Gx^2 + Gy^2
            B = round(sqrt(Bs));
            G = round(sqrt(Gs));
            R = round(sqrt(Rs));

            //capping at 255
            if (B > 255)
            {
                B = 255;
            }

            if (G > 255)
            {
                G = 255;
            }

            if (R > 255)
            {
                R = 255;
            }
            // Setting new RGB
            image[h][w].rgbtBlue = B;
            image[h][w].rgbtGreen = G;
            image[h][w].rgbtRed = R;
        }
    }
    return;
}
