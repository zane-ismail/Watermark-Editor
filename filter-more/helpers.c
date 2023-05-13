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
    RGBTRIPLE temp[height][width];
    float blue_avg = 0.0;
    float green_avg = 0.0;
    float red_avg = 0.0;

    // store original pixel values in temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // iterate through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float pixel_count = 0.0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // pass over edge cases
                    if (i + y < 0 || i + y == height || j + x < 0 || j + x == width)
                    {
                        continue;
                    }

                    // add each pixel together in kernel
                    blue_avg += image[i + y][j + x].rgbtBlue;
                    green_avg += image[i + y][j + x].rgbtGreen;
                    red_avg += image[i + y][j + x].rgbtRed;
                    pixel_count++;

                }
            }
            // create averages
            blue_avg = blue_avg / pixel_count;
            green_avg = green_avg / pixel_count;
            red_avg = red_avg / pixel_count;


            // apply average values to temp pixels
            temp[i][j].rgbtBlue = round(blue_avg);
            temp[i][j].rgbtGreen = round(green_avg);
            temp[i][j].rgbtRed = round(red_avg);
        }
    }

    // apply values to original image pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}







//             // top left corner
//             if (i == 0 && j == 0)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
//                                       image[i + 1][j + 1].rgbtBlue) / 4.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
//                                        image[i + 1][j + 1].rgbtGreen) / 4.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
//                                      image[i + 1][j + 1].rgbtRed) / 4.0;
//             }
//             // top right corner
//             else if (i == 0 && j == width - 1)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
//                                       image[i + 1][j].rgbtBlue) / 4.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
//                                        image[i + 1][j].rgbtGreen) / 4.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
//                                      image[i + 1][j].rgbtRed) / 4.0;

//             }
//             // bottom left corner
//             else if (i == height - 1 && j == 0)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
//                                       image[i][j + 1].rgbtBlue) / 4.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
//                                        image[i][j + 1].rgbtGreen) / 4.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
//                                      image[i][j + 1].rgbtRed) / 4.0;
//             }
//             // bottom right corner
//             else if (i == height - 1 && j == width - 1)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
//                                       image[i][j - 1].rgbtBlue) / 4.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
//                                        image[i][j - 1].rgbtGreen) / 4.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
//                                      image[i][j - 1].rgbtRed) / 4.0;

//             }
//             // top row
//             else if (i == 0)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
//                                       image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
//                                        image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
//                                      image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0;
//             }
//             // left column
//             else if (j == 0)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
//                                       image[i + 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
//                                        image[i + 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
//                                      image[i + 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;
//             }
//             // bottom row
//             else if (i == height - 1)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
//                                       image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
//                                        image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
//                                      image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;
//             }
//             // right column
//             else if (j == width - 1)
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
//                                       image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
//                                        image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
//                                      image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0;
//             }
//             // middle
//             else
//             {
//                 tempblue_avg[i][j] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
//                                       image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
//                                       image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9.0;
//                 tempgreen_avg[i][j] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
//                                        image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
//                                        image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9.0;
//                 tempred_avg[i][j] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
//                                      image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
//                                      image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 9.0;
//             }
//         }
//     }

//     // apply temp values to actual pixels
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             image[i][j].rgbtBlue = round(tempblue_avg[i][j]);
//             image[i][j].rgbtGreen = round(tempgreen_avg[i][j]);
//             image[i][j].rgbtRed = round(tempred_avg[i][j]);
//         }
//     }
// }


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Store values in temporary variable
    float gxblue;
    float gxgreen;
    float gxred;
    float gyblue;
    float gygreen;
    float gyred;
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
                gxblue = (temp[i][j + 1].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen = (temp[i][j + 1].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gxred = (temp[i][j + 1].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);

                gyblue = (temp[i + 1][j].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen = (temp[i + 1][j].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gyred = (temp[i + 1][j].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);
            }

            // top right corner
            else if (i == 0 && j == width - 1)
            {
                gxblue = (temp[i][j - 1].rgbtBlue * - 2) + (temp[i + 1][j - 1].rgbtBlue * - 1);
                gxgreen = (temp[i][j - 1].rgbtGreen * - 2) + (temp[i + 1][j - 1].rgbtGreen * - 1);
                gxred = (temp[i][j - 1].rgbtRed * - 2) + (temp[i + 1][j - 1].rgbtRed * - 1);

                gyblue = (temp[i + 1][j - 1].rgbtBlue * 1) + (temp[i + 1][j].rgbtBlue * 2);
                gygreen = (temp[i + 1][j - 1].rgbtGreen * 1) + (temp[i + 1][j].rgbtGreen * 2);
                gyred = (temp[i + 1][j - 1].rgbtRed * 1) + (temp[i + 1][j].rgbtRed * 2);
            }

            // bottom left corner
            else if (i == height - 1 && j == 0)
            {
                gxblue = (temp[i - 1][j + 1].rgbtBlue * 1) + (temp[i][j + 1].rgbtBlue * 2);
                gxgreen = (temp[i - 1][j + 1].rgbtGreen * 1) + (temp[i][j + 1].rgbtGreen * 2);
                gxred = (temp[i - 1][j + 1].rgbtRed * 1) + (temp[i][j + 1].rgbtRed * 2);

                gyblue = (temp[i - 1][j].rgbtBlue * - 2) + (temp[i - 1][j + 1].rgbtBlue * - 1);
                gygreen = (temp[i - 1][j].rgbtGreen * - 2) + (temp[i - 1][j + 1].rgbtGreen * - 1);
                gyred = (temp[i - 1][j].rgbtRed * - 2) + (temp[i - 1][j + 1].rgbtRed * - 1);
            }

            // bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                gxblue = (temp[i - 1][j - 1].rgbtBlue * - 1) + (temp[i][j - 1].rgbtBlue * - 2);
                gxgreen = (temp[i - 1][j - 1].rgbtGreen * - 1) + (temp[i][j - 1].rgbtGreen * - 2);
                gxred = (temp[i - 1][j - 1].rgbtRed * - 1) + (temp[i][j - 1].rgbtRed * - 2);

                gyblue = (temp[i - 1][j - 1].rgbtBlue  * - 1) + (temp[i - 1][j].rgbtBlue * - 2);
                gygreen = (temp[i - 1][j - 1].rgbtGreen  * - 1) + (temp[i - 1][j].rgbtGreen * - 2);
                gyred = (temp[i - 1][j - 1].rgbtRed  * - 1) + (temp[i - 1][j].rgbtRed * - 2);
            }

            // top row
            else if (i == 0)
            {
                gxblue = (temp[i][j - 1].rgbtBlue * - 2 + temp[i][j + 1].rgbtBlue * 2) +
                         (temp[i + 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen = (temp[i][j - 1].rgbtGreen * - 2 + temp[i][j + 1].rgbtGreen * 2) +
                          (temp[i + 1][j - 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gxred = (temp[i][j - 1].rgbtRed * - 2 + temp[i][j + 1].rgbtRed * 2) +
                        (temp[i + 1][j - 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);

                gyblue = (temp[i + 1][j - 1].rgbtBlue * 1) + (temp[i + 1][j].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen = (temp[i + 1][j - 1].rgbtGreen * 1) + (temp[i + 1][j].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gyred = (temp[i + 1][j - 1].rgbtRed * 1) + (temp[i + 1][j].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);
            }

            // left column
            else if (j == 0)
            {
                gxblue = (temp[i - 1][j + 1].rgbtBlue * 1) + (temp[i][j + 1].rgbtBlue * 2) + (temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen = (temp[i - 1][j + 1].rgbtGreen * 1) + (temp[i][j + 1].rgbtGreen * 2) + (temp[i + 1][j + 1].rgbtGreen * 1);
                gxred = (temp[i - 1][j + 1].rgbtRed * 1) + (temp[i][j + 1].rgbtRed * 2) + (temp[i + 1][j + 1].rgbtRed * 1);

                gyblue = (temp[i - 1][j].rgbtBlue * - 2 + temp[i + 1][j].rgbtBlue * 2) +
                         (temp[i - 1][j + 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen = (temp[i - 1][j].rgbtGreen * - 2 + temp[i + 1][j].rgbtGreen * 2) +
                          (temp[i - 1][j + 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gyred = (temp[i - 1][j].rgbtRed * - 2 + temp[i + 1][j].rgbtRed * 2) +
                        (temp[i - 1][j + 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);
            }

            // bottom row
            else if (i == height - 1)
            {
                gxblue = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i - 1][j + 1].rgbtBlue * 1) +
                         (temp[i][j - 1].rgbtBlue * - 2 + temp[i][j + 1].rgbtBlue * 2);
                gxgreen = (temp[i - 1][j - 1].rgbtGreen * - 1 + temp[i - 1][j + 1].rgbtGreen * 1) +
                          (temp[i][j - 1].rgbtGreen * - 2 + temp[i][j + 1].rgbtGreen * 2);
                gxred = (temp[i - 1][j - 1].rgbtRed * - 1 + temp[i - 1][j + 1].rgbtRed * 1) +
                        (temp[i][j - 1].rgbtRed * - 2 + temp[i][j + 1].rgbtRed * 2);

                gyblue = (temp[i - 1][j - 1].rgbtBlue  * - 1) + (temp[i - 1][j].rgbtBlue * - 2) + (temp[i - 1][j + 1].rgbtBlue * - 1);
                gygreen = (temp[i - 1][j - 1].rgbtGreen  * - 1) + (temp[i - 1][j].rgbtGreen * - 2) + (temp[i - 1][j + 1].rgbtGreen * - 1);
                gyred = (temp[i - 1][j - 1].rgbtRed  * - 1) + (temp[i - 1][j].rgbtRed * - 2) + (temp[i - 1][j + 1].rgbtRed * - 1);
            }

            // right column
            else if (j == width - 1)
            {
                gxblue = (temp[i - 1][j - 1].rgbtBlue * - 1) + (temp[i][j - 1].rgbtBlue * - 2) + (temp[i + 1][j - 1].rgbtBlue * - 1);
                gxgreen = (temp[i - 1][j - 1].rgbtGreen * - 1) + (temp[i][j - 1].rgbtGreen * - 2) + (temp[i + 1][j - 1].rgbtGreen * - 1);
                gxred = (temp[i - 1][j - 1].rgbtRed * - 1) + (temp[i][j - 1].rgbtRed * - 2) + (temp[i + 1][j - 1].rgbtRed * - 1);

                gyblue = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j - 1].rgbtBlue * 1) +
                         (temp[i - 1][j].rgbtBlue * - 2 + temp[i + 1][j].rgbtBlue * 2);
                gygreen = (temp[i - 1][j - 1].rgbtGreen  * - 1 + temp[i + 1][j - 1].rgbtGreen * 1) +
                          (temp[i - 1][j].rgbtGreen * - 2 + temp[i + 1][j].rgbtGreen * 2);
                gyred = (temp[i - 1][j - 1].rgbtRed  * - 1 + temp[i + 1][j - 1].rgbtRed * 1) +
                        (temp[i - 1][j].rgbtRed * - 2 + temp[i + 1][j].rgbtRed * 2);
            }
            else
            {
                gxblue = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i - 1][j + 1].rgbtBlue * 1) + (temp[i][j - 1].rgbtBlue * - 2 +
                         temp[i][j + 1].rgbtBlue * 2) + (temp[i + 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gxgreen = (temp[i - 1][j - 1].rgbtGreen * - 1 + temp[i - 1][j + 1].rgbtGreen * 1) + (temp[i][j - 1].rgbtGreen * - 2 +
                          temp[i][j + 1].rgbtGreen * 2) + (temp[i + 1][j - 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gxred = (temp[i - 1][j - 1].rgbtRed * - 1 + temp[i - 1][j + 1].rgbtRed * 1) + (temp[i][j - 1].rgbtRed * - 2 +
                        temp[i][j + 1].rgbtRed * 2) + (temp[i + 1][j - 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);

                gyblue = (temp[i - 1][j - 1].rgbtBlue * - 1 + temp[i + 1][j - 1].rgbtBlue * 1) + (temp[i - 1][j].rgbtBlue * - 2 +
                         temp[i + 1][j].rgbtBlue * 2) + (temp[i - 1][j + 1].rgbtBlue * - 1 + temp[i + 1][j + 1].rgbtBlue * 1);
                gygreen = (temp[i - 1][j - 1].rgbtGreen  * - 1 + temp[i + 1][j - 1].rgbtGreen * 1) + (temp[i - 1][j].rgbtGreen * - 2 +
                          temp[i + 1][j].rgbtGreen * 2) + (temp[i - 1][j + 1].rgbtGreen * - 1 + temp[i + 1][j + 1].rgbtGreen * 1);
                gyred = (temp[i - 1][j - 1].rgbtRed  * - 1 + temp[i + 1][j - 1].rgbtRed * 1) + (temp[i - 1][j].rgbtRed * - 2 +
                        temp[i + 1][j].rgbtRed * 2) + (temp[i - 1][j + 1].rgbtRed * - 1 + temp[i + 1][j + 1].rgbtRed * 1);
            }

            gblue = round(sqrt((gxblue * gxblue) + (gyblue * gyblue)));
            ggreen = round(sqrt((gxgreen * gxgreen) + (gygreen * gygreen)));
            gred = round(sqrt((gxred * gxred) + (gyred * gyred)));

            // apply temp values to original pixels
            // set limit at 255
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