#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over rows
    for(int i = 0; i < height ; i++)
    {
        // loop over pixels in rows
        for(int j = 0; j < width; j++)
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sepia[3];
            sepia[0] = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            sepia[1] = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            sepia[2] = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            for(int k = 0; k < 3; k++)
            {
                if(sepia[k] > 255)
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0, w = width - 1; j < half; j++, w--)
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image [i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // deal with corners top LHS
            if(i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j+1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen) / 4.0);
                break;

            }
            // top RHS
            else if(i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j-1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j-1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j-1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j-1].rgbtGreen) / 4.0);
                break;

            }
            // now rest of first row
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j+1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i][j-1].rgbtRed + temp[i+1][j-1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i+1][j-1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i+1][j-1].rgbtGreen) / 6.0);
                break;

            }
            // bottom LHS
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j+1].rgbtRed + temp[i-1][j].rgbtRed + temp[i+1][j+1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen) / 4.0);
                break;

            }
            // last column
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j+1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen) / 6.0);
                break;

            }
            // bottom rhs
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j-1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j-1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j-1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j-1].rgbtGreen) / 4.0);
                break;

            }

            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j+1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed + temp[i][j-1].rgbtRed + temp[i-1][j-1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i-1][j-1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i-1][j-1].rgbtGreen) / 6.0);
                break;

            }

            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j-1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j-1].rgbtRed + temp[i-1][j-1].rgbtRed + temp[i-1][j].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j-1].rgbtBlue + temp[i-1][j-1].rgbtBlue + temp[i-1][j].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j-1].rgbtGreen + temp[i-1][j-1].rgbtGreen + temp[i-1][j].rgbtGreen) / 6.0);
                break;

            }
            else
            {
                image[i][j].rgbtRed = round((temp[i][j].rgbtRed + temp[i][j+1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i][j-1].rgbtRed + temp[i-1][j-1].rgbtRed + temp[i+1][j-1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed) / 9.0);
                image[i][j].rgbtBlue = round((temp[i][j].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i-1][j-1].rgbtBlue + temp[i+1][j-1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue) / 9.0);
                image[i][j].rgbtGreen = round((temp[i][j].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i-1][j-1].rgbtGreen + temp[i+1][j-1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen) / 9.0);
            }
        }
    }
    return;
}
