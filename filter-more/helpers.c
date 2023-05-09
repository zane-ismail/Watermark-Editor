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
    int tempblue[height][width];
    int tempgreen[height][width];
    int tempred[height][width];
    int x = 1;

    // begin with right most pixel and work left
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempblue[i][j] = image[i][width - x].rgbtBlue;
            tempgreen[i][j] = image[i][width - x].rgbtGreen;
            tempred[i][j] = image[i][width - x].rgbtRed;
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
    double tempblue_avg[height][width];
    double tempgreen_avg[height][width];
    double tempred_avg[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k == )
                }
            }
        }
    }



    // apply temp values to actual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = round(tempblue_avg[i][j]);
            image[i][j].rgbtGreen = round(tempgreen_avg[i][j]);
            image[i][j].rgbtRed = round(tempred_avg[i][j]);
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