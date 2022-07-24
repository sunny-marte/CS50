#include "helpers.h"
#include <math.h>
#include <stdio.h>

void swap(BYTE *a, BYTE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            BYTE average = (BYTE) rintf(sum / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            image[i][j].rgbtRed = (BYTE) rintf(fmin(255.0, sepiaRed));
            image[i][j].rgbtGreen = (BYTE) rintf(fmin(255.0, sepiaGreen));
            image[i][j].rgbtBlue = (BYTE) rintf(fmin(255.0, sepiaBlue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == width - j - 1) //if width is odd and indexes reach the same middle index
            {
                break;
            }
            else if (j == width / 2 && width - j - 1 == j - 1)// if width is even and indexes start going past the middle and each other
            {
                break;
            }

            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //make a copy of the image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            *&copy[i][j].rgbtBlue = *&image[i][j].rgbtBlue;
            *&copy[i][j].rgbtGreen = *&image[i][j].rgbtGreen;
            *&copy[i][j].rgbtRed = *&image[i][j].rgbtRed;
        }
    }

    //find the 4 pixel corners of the image and blur them
    image[0][0].rgbtBlue = (BYTE) round((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = (BYTE) round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen + copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = (BYTE) round((copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);

    image[0][width - 1].rgbtBlue = (BYTE) round((copy[0][width - 1].rgbtBlue + copy[0][width - 2].rgbtBlue + copy[1][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = (BYTE) round((copy[0][width - 1].rgbtGreen + copy[0][width - 2].rgbtGreen + copy[1][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = (BYTE) round((copy[0][width - 1].rgbtRed + copy[0][width - 2].rgbtRed + copy[1][width - 1].rgbtRed + copy[1][width - 2].rgbtRed) / 4.0);

    image[height - 1][0].rgbtBlue = (BYTE) round((copy[height - 1][0].rgbtBlue + copy[height - 1][1].rgbtBlue + copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtGreen = (BYTE) round((copy[height - 1][0].rgbtGreen + copy[height - 1][1].rgbtGreen + copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtRed = (BYTE) round((copy[height - 1][0].rgbtRed + copy[height - 1][1].rgbtRed + copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed) / 4.0);

    image[height - 1][width - 1].rgbtBlue = (BYTE) round((copy[height - 1][width - 1].rgbtBlue + copy[height - 1][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue + copy[height - 2][width - 2].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtGreen = (BYTE) round((copy[height - 1][width - 1].rgbtGreen + copy[height - 1][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen + copy[height - 2][width - 2].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtRed = (BYTE) round((copy[height - 1][width - 1].rgbtRed + copy[height - 1][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed + copy[height - 2][width - 2].rgbtRed) / 4.0);

    //blur the remaining pixels
    for (int k = 1; k < height - 1; k++)
    {
        for (int l = 1; l < width - 1; l++)
        {
            //blurring the middle pixels
            image[k][l].rgbtBlue =  (BYTE) round((copy[k - 1][l - 1].rgbtBlue + copy[k - 1][l].rgbtBlue + copy[k - 1][l + 1].rgbtBlue +
                                                  copy[k][l - 1].rgbtBlue + copy[k][l].rgbtBlue + copy[k][l + 1].rgbtBlue +
                                                  copy[k + 1][l - 1].rgbtBlue + copy[k + 1][l].rgbtBlue + copy[k + 1][l + 1].rgbtBlue) / 9.0);
            image[k][l].rgbtGreen =  (BYTE) round((copy[k - 1][l - 1].rgbtGreen + copy[k - 1][l].rgbtGreen + copy[k - 1][l + 1].rgbtGreen +
                                                   copy[k][l - 1].rgbtGreen + copy[k][l].rgbtGreen + copy[k][l + 1].rgbtGreen +
                                                   copy[k + 1][l - 1].rgbtGreen + copy[k + 1][l].rgbtGreen + copy[k + 1][l + 1].rgbtGreen) / 9.0);
            image[k][l].rgbtRed =  (BYTE) round((copy[k - 1][l - 1].rgbtRed + copy[k - 1][l].rgbtRed + copy[k - 1][l + 1].rgbtRed +
                                                 copy[k][l - 1].rgbtRed + copy[k][l].rgbtRed + copy[k][l + 1].rgbtRed +
                                                 copy[k + 1][l - 1].rgbtRed + copy[k + 1][l].rgbtRed + copy[k + 1][l + 1].rgbtRed) / 9.0);

            //top edge
            image[0][l].rgbtBlue = (BYTE) round((copy[0][l - 1].rgbtBlue + copy[0][l].rgbtBlue + copy[0][l + 1].rgbtBlue +
                                                 copy[1][l - 1].rgbtBlue + copy[1][l].rgbtBlue + copy[1][l + 1].rgbtBlue) / 6.0);
            image[0][l].rgbtGreen = (BYTE) round((copy[0][l - 1].rgbtGreen + copy[0][l].rgbtGreen + copy[0][l + 1].rgbtGreen +
                                                  copy[1][l - 1].rgbtGreen + copy[1][l].rgbtGreen + copy[1][l + 1].rgbtGreen) / 6.0);
            image[0][l].rgbtRed = (BYTE) round((copy[0][l - 1].rgbtRed + copy[0][l].rgbtRed + copy[0][l + 1].rgbtRed +
                                                copy[1][l - 1].rgbtRed + copy[1][l].rgbtRed + copy[1][l + 1].rgbtRed) / 6.0);

            //bottom edge
            image[height - 1][l].rgbtBlue = (BYTE) round((copy[height - 2][l - 1].rgbtBlue + copy[height - 2][l].rgbtBlue + copy[height - 2][l + 1].rgbtBlue +
                                                          copy[height - 1][l - 1].rgbtBlue + copy[height - 1][l].rgbtBlue + copy[height - 1][l + 1].rgbtBlue) / 6.0);
            image[height - 1][l].rgbtGreen = (BYTE) round((copy[height - 2][l - 1].rgbtGreen + copy[height - 2][l].rgbtGreen + copy[height - 2][l + 1].rgbtGreen +
                                                          copy[height - 1][l - 1].rgbtGreen + copy[height - 1][l].rgbtGreen + copy[height - 1][l + 1].rgbtGreen) / 6.0);
            image[height - 1][l].rgbtRed = (BYTE) round((copy[height - 2][l - 1].rgbtRed + copy[height - 2][l].rgbtRed + copy[height - 2][l + 1].rgbtRed +
                                                          copy[height - 1][l - 1].rgbtRed + copy[height - 1][l].rgbtRed + copy[height - 1][l + 1].rgbtRed) / 6.0);

            //left edge
            image[k][0].rgbtBlue = (BYTE) round((copy[k - 1][0].rgbtBlue + copy[k - 1][1].rgbtBlue +
                                                 copy[k][0].rgbtBlue + copy[k][1].rgbtBlue +
                                                 copy[k + 1][0].rgbtBlue + copy[k + 1][1].rgbtBlue) / 6.0);
            image[k][0].rgbtGreen = (BYTE) round((copy[k - 1][0].rgbtGreen + copy[k - 1][1].rgbtGreen +
                                                  copy[k][0].rgbtGreen + copy[k][1].rgbtGreen +
                                                  copy[k + 1][0].rgbtGreen + copy[k + 1][1].rgbtGreen) / 6.0);
            image[k][0].rgbtRed = (BYTE) round((copy[k - 1][0].rgbtRed + copy[k - 1][1].rgbtRed +
                                                copy[k][0].rgbtRed + copy[k][1].rgbtRed +
                                                copy[k + 1][0].rgbtRed + copy[k + 1][1].rgbtRed) / 6.0);

            //right edge
            image[k][width - 1].rgbtBlue =  (BYTE) round((copy[k - 1][width - 2].rgbtBlue + copy[k - 1][width - 1].rgbtBlue +
                                                          copy[k][width - 2].rgbtBlue + copy[k][width - 1].rgbtBlue +
                                                          copy[k + 1][width - 2].rgbtBlue + copy[k + 1][width - 1].rgbtBlue) / 6.0);
            image[k][width - 1].rgbtGreen =  (BYTE) round((copy[k - 1][width - 2].rgbtGreen + copy[k - 1][width - 1].rgbtGreen +
                                                           copy[k][width - 2].rgbtGreen + copy[k][width - 1].rgbtGreen +
                                                           copy[k + 1][width - 2].rgbtGreen + copy[k + 1][width - 1].rgbtGreen) / 6.0);
            image[k][width - 1].rgbtRed =  (BYTE) round((copy[k - 1][width - 2].rgbtRed + copy[k - 1][width - 1].rgbtRed +
                                                         copy[k][width - 2].rgbtRed + copy[k][width - 1].rgbtRed +
                                                         copy[k + 1][width - 2].rgbtRed + copy[k + 1][width - 1].rgbtRed) / 6.0);
        }
    }
    return;
}

void swap(BYTE *a, BYTE *b)
{
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
}