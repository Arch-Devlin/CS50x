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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Setup variables
            int OB = image[h][w].rgbtBlue;
            int OG = image[h][w].rgbtGreen;
            int OR = image[h][w].rgbtRed;

            // calculate new GRB
            float fNB = 0.272 * OR + 0.534 * OG + 0.131 * OB;
            float fNG = 0.349 * OR + 0.686 * OG + 0.168 * OB;
            float fNR = 0.393 * OR + 0.769 * OG + 0.189 * OB;

            int NB = round(fNB);
            int NG = round(fNG);
            int NR = round(fNR);

            //Checking if abouve 255 and setting to 255 if yes else setting as new RGB
            if (NB >= 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = NB;
            }

            if (NG >= 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = NG;
            }

            if (NR >= 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = NR;
            }


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
            //seting tep pixl aray
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
