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
            // create temporary array to store new values
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
    double tempblue_avg[height][width];
    double tempgreen_avg[height][width];
    double tempred_avg[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            if (i == 0 && j == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                      image[i + 1][j + 1].rgbtBlue) / 4.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen) / 4.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                     image[i + 1][j + 1].rgbtRed) / 4.0;
            }
            // top right corner
            else if (i == 0 && j == width - 1)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                      image[i + 1][j].rgbtBlue) / 4.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                       image[i + 1][j].rgbtGreen) / 4.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                     image[i + 1][j].rgbtRed) / 4.0;

            }
            // bottom left corner
            else if (i == height - 1 && j == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                      image[i][j + 1].rgbtBlue) / 4.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                       image[i][j + 1].rgbtGreen) / 4.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                     image[i][j + 1].rgbtRed) / 4.0;
            }
            // bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                      image[i][j - 1].rgbtBlue) / 4.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                       image[i][j - 1].rgbtGreen) / 4.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                     image[i][j - 1].rgbtRed) / 4.0;

            }
            // top row
            else if (i == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                      image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                       image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                     image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0;
            }
            // left column
            else if (j == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                      image[i + 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                     image[i + 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;
            }
            // bottom row
            else if (i == height - 1)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                      image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                     image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;
            }
            // right column
            else if (j == width - 1)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                      image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                       image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                     image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0;
            }
            // middle
            else
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                      image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                      image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                       image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                     image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                     image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 9.0;
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
    float gxblue[height][width];
    float gxgreen[height][width];
    float gxred[height][width];
    float gyblue[height][width];
    float gygreen[height][width];
    float gyred[height][width];
    float gblue;
    float ggreen;
    float gred;
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // create temporary array to store new values
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            if (i == 0 && j == 0)
            {
                gxblue[i][j] = (temp[i][j + 1].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen[i][j] = (temp[i][j + 1].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gxred[i][j] =  (temp[i][j + 1].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);

                gyblue[i][j] = (temp[i + 1][j].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen[i][j] = (temp[i + 1][j].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gyred[i][j] = (temp[i + 1][j].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);
            }
            // top right corner
            if (i == 0 && j == width - 1)
            {
                gxblue[i][j] = (temp[i][j - 1].rgbtBlue * - 2) + (temp[i + 1][j - 1].rgbtBlue * - 1);
                gxgreen[i][j] = (temp[i][j - 1].rgbtGreen * - 2) + (temp[i + 1][j - 1].rgbtGreen * - 1);
                gxred[i][j] =  (temp[i][j - 1].rgbtRed * - 2) + (temp[i + 1][j - 1].rgbtRed * - 1);

                gyblue[i][j] = (temp[i + 1][j - 1].rgbtBlue * 1) +(temp[i + 1][j].rgbtBlue * 2);
                gygreen[i][j] = (temp[i + 1][j - 1].rgbtGreen * 1) + (temp[i + 1][j].rgbtGreen * 2);
                gyred[i][j] = (temp[i + 1][j - 1].rgbtRed * 1) + (temp[i + 1][j].rgbtRed * 2);
            }
            // bottom left corner
            if (i == height - 1 && j == 0)
            {
                gxblue[i][j] = (temp[i - 1][j + 1].rgbtBlue * 1) + (temp[i][j + 1].rgbtBlue * 2);
                gxgreen[i][j] = (temp[i - 1][j + 1].rgbtGreen * 1) + (temp[i][j + 1].rgbtGreen * 2);
                gxred[i][j] = (temp[i - 1][j + 1].rgbtRed * 1) + (temp[i][j + 1].rgbtRed * 2);

                gyblue[i][j] = (temp[i - 1][j].rgbtBlue * - 2) + (temp[i - 1][j + 1].rgbtBlue * - 1);
                gygreen[i][j] = (temp[i - 1][j].rgbtGreen * - 2) + (temp[i - 1][j + 1].rgbtGreen * - 1);
                gyred[i][j] = (temp[i - 1][j].rgbtRed * - 2) + (temp[i - 1][j + 1].rgbtRed * - 1);
            }
            // bottom right corner
            if (i == height - 1 && j == width - 1)
            {
                gxblue[i][j] = (temp[i - 1][j - 1].rgbtBlue * - 1) + (temp[i][j - 1].rgbtBlue * - 2);
                gxgreen[i][j] = (temp[i - 1][j - 1].rgbtGreen * - 1) + (temp[i][j - 1].rgbtGreen * - 2);
                gxred[i][j] = (temp[i - 1][j - 1].rgbtRed * - 1) + (temp[i][j - 1].rgbtRed * - 2);

                gyblue[i][j] = (temp[i - 1][j - 1].rgbtBlue  * - 1) + (temp[i - 1][j].rgbtBlue * - 2);
                gygreen[i][j] = (temp[i - 1][j - 1].rgbtGreen  * - 1) + (temp[i - 1][j].rgbtGreen * - 2);
                gyred[i][j] = (temp[i - 1][j - 1].rgbtRed  * - 1) + (temp[i - 1][j].rgbtRed * - 2);
            }
            // top row
            if (i == 0)
            {
                gxblue[i][j] = (temp[i][j - 1].rgbtBlue * - 2 + temp[i][j + 1].rgbtBlue * 2) +
                                (temp[i + 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen[i][j] = (temp[i][j - 1].rgbtGreen * - 2 + temp[i][j + 1].rgbtGreen * 2) +
                                (temp[i + 1][j - 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gxred[i][j] = (temp[i][j - 1].rgbtRed * - 2 + temp[i][j + 1].rgbtRed * 2) +
                                (temp[i + 1][j - 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);

                gyblue[i][j] = (temp[i + 1][j - 1].rgbtBlue * 1) + (temp[i + 1][j].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen[i][j] = (temp[i + 1][j - 1].rgbtGreen * 1) + (temp[i + 1][j].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gyred[i][j] = (temp[i + 1][j - 1].rgbtRed * 1) + (temp[i + 1][j].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);
            }
            // left column
            if (j == 0)
            {
                gxblue[i][j] = (temp[i - 1][j + 1].rgbtBlue * 1) + (temp[i][j + 1].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen[i][j] = (temp[i - 1][j + 1].rgbtGreen * 1) + (temp[i][j + 1].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gxred[i][j] = (temp[i - 1][j + 1].rgbtRed * 1) + (temp[i][j + 1].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);

                gyblue[i][j] = (temp[i - 1][j].rgbtBlue * - 2 + temp[i + 1][j].rgbtBlue * 2) +
                                (temp[i - 1][j + 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen[i][j] = (temp[i - 1][j].rgbtGreen * - 2 + temp[i + 1][j].rgbtGreen * 2) +
                                (temp[i - 1][j + 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gyred[i][j] = (temp[i - 1][j].rgbtRed * - 2 + temp[i + 1][j].rgbtRed * 2) +
                                (temp[i - 1][j + 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);
            }
            // bottom row
            if (i == height - 1)
            {
                gxblue[i][j] = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i - 1][j + 1].rgbtBlue * 1) +
                                (temp[i][j - 1].rgbtBlue * - 2 + temp[i][j + 1].rgbtBlue * 2);
                gxgreen[i][j] = (temp[i - 1][j - 1].rgbtGreen * - 1 + temp[i - 1][j + 1].rgbtGreen * 1) +
                                (temp[i][j - 1].rgbtGreen * - 2 + temp[i][j + 1].rgbtGreen * 2);
                gxred[i][j] = (temp[i - 1][j - 1].rgbtRed * - 1 + temp[i - 1][j + 1].rgbtRed * 1) +
                                (temp[i][j - 1].rgbtRed * - 2 + temp[i][j + 1].rgbtRed * 2);

                gyblue[i][j] = (temp[i - 1][j - 1].rgbtBlue  * - 1) + (temp[i - 1][j].rgbtBlue * - 2) + (temp[i - 1][j + 1].rgbtBlue * - 1);
                gygreen[i][j] = (temp[i - 1][j - 1].rgbtGreen  * - 1) + (temp[i - 1][j].rgbtGreen * - 2) + (temp[i - 1][j + 1].rgbtGreen * - 1);
                gyred[i][j] = (temp[i - 1][j - 1].rgbtRed  * - 1) + (temp[i - 1][j].rgbtRed * - 2) + (temp[i - 1][j + 1].rgbtRed * - 1);
            }
            // right column
            if (j == width - 1)
            {
                gxblue[i][j] = (temp[i - 1][j - 1].rgbtBlue * - 1) +
                                (temp[i][j - 1].rgbtBlue * - 2) +
                                (temp[i + 1][j - 1].rgbtBlue * - 1);
                gxgreen[i][j] = (temp[i - 1][j - 1].rgbtGreen * - 1) +
                                (temp[i][j - 1].rgbtGreen * - 2) +
                                (temp[i + 1][j - 1].rgbtGreen * - 1);
                gxred[i][j] = (temp[i - 1][j - 1].rgbtRed * - 1) +
                                (temp[i][j - 1].rgbtRed * - 2) +
                                (temp[i + 1][j - 1].rgbtRed * - 1);

                gyblue[i][j] = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j - 1].rgbtBlue * 1) +
                                (temp[i - 1][j].rgbtBlue * - 2 + temp[i + 1][j].rgbtBlue * 2);
                gygreen[i][j] = (temp[i - 1][j - 1].rgbtGreen  * - 1 + temp[i + 1][j - 1].rgbtGreen * 1) +
                                (temp[i - 1][j].rgbtGreen * - 2 + temp[i + 1][j].rgbtGreen * 2);
                gyred[i][j] = (temp[i - 1][j - 1].rgbtRed  * - 1 + temp[i + 1][j - 1].rgbtRed * 1) +
                                (temp[i - 1][j].rgbtRed * - 2 + temp[i + 1][j].rgbtRed * 2);
            }
            else
            {
                gxblue[i][j] = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i - 1][j + 1].rgbtBlue * 1) +
                                (temp[i][j - 1].rgbtBlue * - 2 + temp[i][j + 1].rgbtBlue * 2) +
                                (temp[i + 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen[i][j] = (temp[i - 1][j - 1].rgbtGreen * - 1 + temp[i - 1][j + 1].rgbtGreen * 1) +
                                (temp[i][j - 1].rgbtGreen * - 2 + temp[i][j + 1].rgbtGreen * 2) +
                                (temp[i + 1][j - 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gxred[i][j] = (temp[i - 1][j - 1].rgbtRed * - 1 + temp[i - 1][j + 1].rgbtRed * 1) +
                                (temp[i][j - 1].rgbtRed * - 2 + temp[i][j + 1].rgbtRed * 2) +
                                (temp[i + 1][j - 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);

                gyblue[i][j] = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j - 1].rgbtBlue * 1) +
                                (temp[i - 1][j].rgbtBlue * - 2 + temp[i + 1][j].rgbtBlue * 2) +
                                (temp[i - 1][j + 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen[i][j] = (temp[i - 1][j - 1].rgbtGreen  * - 1 + temp[i + 1][j - 1].rgbtGreen * 1) +
                                (temp[i - 1][j].rgbtGreen * - 2 + temp[i + 1][j].rgbtGreen * 2) +
                                (temp[i - 1][j + 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gyred[i][j] = (temp[i - 1][j - 1].rgbtRed  * - 1 + temp[i + 1][j - 1].rgbtRed * 1) +
                                (temp[i - 1][j].rgbtRed * - 2 + temp[i + 1][j].rgbtRed * 2) +
                                (temp[i - 1][j + 1].rgbtRed * - 1 + image[i + 1][j + 1].rgbtRed * 1);
            }

            gblue = round(sqrt((gxblue * gxblue) + (gyblue * gyblue)));
            ggreen = round(sqrt((gxgreen] * gxgreen) + (gygreen * gygreen)));
            gred = round(sqrt((gxred * gxred) + (gyred * gyred)));


    // apply temp values to actual pixels

            if (gblue >= 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(gblue);
            }
            if (ggreen >= 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(ggreen);
            }
            if (gred >= 255)
            {
                image[i][j].rgbtRed = 255;
            }

            else
            {
                image[i][j].rgbtRed = round(gred);
            }
        }
    }
}