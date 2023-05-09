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
    RGBTRIPLE temp[height][width];
    int x = 1;

    // begin with right most pixel and work left
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][width - x];
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
            image[i][j] = temp[i][j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Store values in temporary variable
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise values
            double r_sum = 0;
            double b_sum = 0;
            double g_sum = 0;
            int count = 0;

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    temp[i][j] = image[i][j];
                }
            }

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    for (int k = -1; k < 2; k++)
                    {
                        for (int l = -1; l <2; l++)
                        {
                            if (i + k < 0 || i + k == height)
                            {
                                continue;
                            }
                            else if (j + l < 0 || j + l == width)
                            {
                                continue;
                            }
                            b_sum += temp[i + k][j + l].rgbtBlue;
                            g_sum += temp[i + k][j + l].rgbtGreen;
                            r_sum += temp[i + k][j + l].rgbtRed;
                            count++;
                        }
                    }
                }
            }

            image[i][j].rgbtRed = round(b_sum / count);
            image[i][j].rgbtGreen = round(g_sum / count);
            image[i][j].rgbtBlue = round(r_sum / count);
        }
    }
}

    // apply temp values to actual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = round(temp[i][j]);
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