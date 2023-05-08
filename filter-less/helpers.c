#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // When implementing the grayscale function, you’ll need to average the values of 3 integers
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue != image[i][j].rgbtGreen || image[i][j].rgbtRed != image[i][j].rgbtBlue || image[i][j].rgbtGreen != image[i][j].rgbtRed)
            {
                double average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
                int avg = round(average);

                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtRed = avg;
            }
        }
    }

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sr = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            double sg = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            double sb = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaRed = round(sr);
            int sepiaGreen = round(sg);
            int sepiaBlue = round (sb);


            if (sepiaBlue <= 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
            if (sepiaGreen <= 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepiaRed <= 255)
            {
               image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // printf("Height %i\n", height);
    // printf("Width %i\n", width);
    int x = 1;
    int tempblue[height][width];
    int tempgreen[height][width];
    int tempred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempblue[i][j] = image[i][width-x].rgbtBlue;
            tempgreen[i][j] = image[i][width-x].rgbtGreen;
            tempred[i][j] = image[i][width-x].rgbtRed;
            x++;
            if (x == width+1)
            {
                x = 1;
            }
        }
    }
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
    // printf("Height %i\n", height);
    // printf("Width %i\n", width);
    double tempblue_avg[height][width];
    double tempgreen_avg[height][width];
    double tempred_avg[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 4.0;
                tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 4.0;
                tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 4.0;
            }
            if (i == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0;
                tempblue_avg[i][j] = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0;
                tempblue_avg[i][j] = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0;
            }
            if (j == 0)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue) / 6.0;
                tempblue_avg[i][j] = (image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen) / 6.0;
                tempblue_avg[i][j] = (image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed) / 6.0;
            }
            else if (i == height-1)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue) / 6.0;
                tempblue_avg[i][j] = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen) / 6.0;
                tempblue_avg[i][j] = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed) / 6.0;
            }
            else if (j == width)
            {
                tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) / 6.0;

            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i != 0 && i != height-1 && j != 0 && j != width-1)
            {
                image[i][j].rgbtBlue = round(tempblue_avg[i][j]);
                image[i][j].rgbtGreen = round(tempgreen_avg[i][j]);
                image[i][j].rgbtRed = round(tempred_avg[i][j]);
            }
        }
    }
}
