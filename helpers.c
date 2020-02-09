#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over rows
    for (int i = 0; i < height ; i++)
    {
        // loop over pixels in rows
        for (int j = 0; j < width; j++)
        {
            int grey = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia[3];
            sepia[0] = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            sepia[1] = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            sepia[2] = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            for (int k = 0; k < 3; k++)
            {
                if (sepia[k] > 255)
                {
                    sepia[k] = 255;
                }
            }
            image[i][j].rgbtRed = sepia[0];
            image[i][j].rgbtGreen = sepia[1];
            image[i][j].rgbtBlue = sepia[2];

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = round(width / 2.0);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, w = width - 1; j < half; j++, w--)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][w];
            image[i][w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy of image that we can use to calculate and not mess with original
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image [i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int aver_red = 0;
            int aver_blue = 0;
            int aver_green = 0;
            int count = 0;
            // check to see if surrounding pixels exist
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if (a < 0 || a > height - 1 || b < 0 || b > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        // add that pixel to average calc plus a counter to keep track
                        aver_red += temp[a][b].rgbtRed;
                        aver_blue += temp[a][b].rgbtBlue;
                        aver_green += temp[a][b].rgbtGreen;
                        count++;
                    }
                }
            }
            aver_red = round((float)aver_red / count);
            aver_blue = round((float)aver_blue / count);
            aver_green = round((float)aver_green / count);
            image[i][j].rgbtRed = aver_red;
            image[i][j].rgbtBlue = aver_blue;
            image[i][j].rgbtGreen = aver_green;
        }
    }

    return;
}
