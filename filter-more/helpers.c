#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // ensure pixels are not gray
            if (image[i][j].rgbtBlue != image[i][j].rgbtGreen || image[i][j].rgbtRed != image[i][j].rgbtBlue
                || image[i][j].rgbtGreen != image[i][j].rgbtRed)
            {
                // average the values of 3 integers to make gray
                double average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
                int avg = round(average);

                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtRed = avg;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Store values in temporary variable
    int RGBT temp[height][width];
    int x = 1;

    // begin with right most pixel and work left
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][width - x].rgbtBlue;
            x++;
            // reset x value at the end (leftside) of the row
            if (x == width + 1)
            {
                x = 1;
            }
        }
    }

    // apply temp values to actual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tempblue[i][j];
            image[i][j].rgbtGreen = tempgreen[i][j];
            image[i][j].rgbtRed = tempred[i][j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Store values in temporary variable
    double RGBT temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            if (i == 0 && j == 0)
            {
                RGBT temp[i][j] = (image[i][j] + image[i][j + 1] + image[i + 1][j] +
                                      image[i + 1][j + 1] / 4.0;
            }
            // top right corner
            else if (i == 0 && j == width - 1)
            {
                RGBT temp[i][j] = (image[i][j] + image[i][j - 1] + image[i + 1][j - 1] +
                                      image[i + 1][j]) / 4.0;

            }
            // bottom left corner
            else if (i == height - 1 && j == 0)
            {
                RGBT temp[i][j] = (image[i][j] + image[i - 1][j] + image[i - 1][j + 1] +
                                      image[i][j + 1]) / 4.0;
            }
            // bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                RGBT temp[i][j] = (image[i][j] + image[i - 1][j] + image[i - 1][j - 1] +
                                      image[i][j - 1]) / 4.0;
            }
            // top row
            else if (i == 0)
            {
                RGBT temp[i][j] = (image[i][j] + image[i][j - 1] + image[i][j + 1] +
                                      image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 6.0;
            }
            // left column
            else if (j == 0)
            {
                RGBT temp[i][j] = (image[i][j] + image[i][j + 1] + image[i + 1][j] +
                                      image[i + 1][j + 1] + image[i - 1][j] + image[i - 1][j + 1]) / 6.0;
            }
            // bottom row
            else if (i == height - 1)
            {
                RGBT temp[i][j] = (image[i][j] + image[i][j - 1] + image[i][j + 1] +
                                      image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1]) / 6.0;
            }
            // right column
            else if (j == width - 1)

                RGBT temp[i][j] = (image[i][j] + image[i - 1][j] + image[i - 1][j - 1] +
                                      image[i][j - 1] + image[i + 1][j] + image[i + 1][j - 1]) / 6.0;
            }
            // middle
            else
            {
                RGBT temp[i][j] = (image[i][j] + image[i - 1][j] + image[i - 1][j - 1] +
                                      image[i][j - 1] + image[i + 1][j] + image[i + 1][j - 1] +
                                      image[i + 1][j + 1] + image[i][j + 1] + image[i - 1][j + 1]) / 9.0;
            }
        }
    }

    // apply temp values to actual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = round(RGBT temp[i][j]);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Store values in temporary variable
    double tempblue[height][width];
    double tempgreen[height][width];
    double tempred[height][width];
    double gxblue;
    double gxgreen;
    double gxred;
    double gyblue;
    double gygreen;
    double gyred;
    double gblue;
    double ggreen;
    double gred;
    int b;
    int g;
    int r;
}