#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // Store the average
    int average;

    // Iterate around rows
    for (int i = 0; i < height; i++)
    {
        // Iterate around the columns
        for (int j = 0; j < width; j++)
        {
            // Compute average with floating variable and round to the nearest number
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Assign average to each color
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Store one reflect row of pixels at a time
    RGBTRIPLE reflect[width];

    for (int i = 0; i < height; i++)
    {
        

        // Iterate around each column and assign the reflected value to array reflect
        for (int j = 0; j < width; j++)
        {
            reflect[j].rgbtBlue = image[i][width - (1 + j)].rgbtBlue;
            reflect[j].rgbtGreen = image[i][width - (1 + j)].rgbtGreen;
            reflect[j].rgbtRed =  image[i][width - (1 + j)].rgbtRed;
        }

        // Iterate around each column and assign the value of reflect array to image array
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtBlue = reflect[k].rgbtBlue;
            image[i][k].rgbtGreen = reflect[k].rgbtGreen;
            image[i][k].rgbtRed = reflect[k].rgbtRed;
        }
    }
    return;
}

// blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Store blur media
    RGBTRIPLE blur[height][width];

    // Iterate around each row
    for (int i = 0; i < height; i++)
    {

        // Iterate around each column and assign the blur value to array blur
        for (int j = 0; j < width; j++)
        {

            // Corner top-left
            if (i == 0 && j == 0)
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
            }
            // Corner top-right
            else if (i == 0 && j == width - 1)
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0);
            }
            // Corner bottom-left
            else if (i == height - 1 && j == 0)
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0);
            }
            // Corner bottom-right
            else if (i == height - 1 && j == width - 1)
            {
                 blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0);
                 blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
                 blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
            }

            // Other pixel in first column
            else if ((i != 0 && i != height - 1)  && j == 0)
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
            }

            // Other pixels in last column
            else if ((i != 0 && i != height - 1)  && j == width - 1)
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);

            }

            // Other pixels in first row
            else if (i == 0 && (j != 0 && j != width - 1))
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
            }

            // Other pixels in last row
            else if (i == height - 1 && (j != 0 && j != width - 1))
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
            }

            // All other pixels
            else
            {
                blur[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                blur[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
                blur[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
            }
        }
    }

    // Iterate around each row
    for (int k = 0; k < height; k++)
    {
        // Iterate around each column and assign the value of reflect array to image array
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtBlue = blur[k][l].rgbtBlue;
            image[k][l].rgbtGreen = blur[k][l].rgbtGreen;
            image[k][l].rgbtRed = blur[k][l].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Store modified image
    RGBTRIPLE edges[height][width];
    
    // Store temp Gx and Gy values
    int gx_rgbtGreen;
    int gx_rgbtBlue;
    int gx_rgbtRed;
    int gy_rgbtGreen;
    int gy_rgbtBlue;
    int gy_rgbtRed;
    
    // Store final value that will be transferred to the edge array
    long edgesgreen;
    long edgesblue;
    long edgesred;
    
    // Iterate around each row
    for (int i = 0; i < height; i++)
    {

        // Iterate around each column and assign the edges value to array edges
        for (int j = 0; j < width; j++)
        {
    
            // Corner top-left
            if (i == 0 && j == 0)
            {
                // Gx compute
                gx_rgbtGreen = (image[i][j + 1].rgbtGreen * 2) + image[i + 1][j + 1].rgbtGreen;
                gx_rgbtBlue = (image[i][j + 1].rgbtBlue * 2) + image[i + 1][j + 1].rgbtBlue;
                gx_rgbtRed = (image[i][j + 1].rgbtRed * 2) + image[i + 1][j + 1].rgbtRed;

                // Gy compute
                gy_rgbtGreen = (image[i + 1][j].rgbtGreen * 2) + image[i + 1][j + 1].rgbtGreen;
                gy_rgbtBlue = (image[i + 1][j].rgbtBlue * 2) + image[i + 1][j + 1].rgbtBlue;
                gy_rgbtRed = (image[i + 1][j].rgbtRed * 2) + image[i + 1][j + 1].rgbtRed;
                
            }
            
            // Corner top-right
            else if (i == 0 && j == width - 1)
            {
                
                // Gx compute
                gx_rgbtGreen = (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1);
                gx_rgbtBlue = (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1);
                gx_rgbtRed = (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1);
                
                // Gy compute
                gy_rgbtGreen = image[i + 1][j - 1].rgbtGreen + (image[i + 1][j].rgbtGreen * 2);
                gy_rgbtBlue = image[i + 1][j - 1].rgbtBlue + (image[i + 1][j].rgbtBlue * 2);
                gy_rgbtRed = image[i + 1][j - 1].rgbtRed + (image[i + 1][j].rgbtRed * 2);
                
            
            }
            
            // Corner bottom-left
            else if (i == height - 1 && j == 0)
            {
                // Gx compute
                gx_rgbtGreen = (image[i][j + 1].rgbtGreen * 2) + image[i - 1][j + 1].rgbtGreen;
                gx_rgbtBlue = (image[i][j + 1].rgbtBlue * 2) + image[i - 1][j + 1].rgbtBlue;
                gx_rgbtRed = (image[i][j + 1].rgbtRed * 2) + image[i - 1][j + 1].rgbtRed;
                
                // Gy compute
                gy_rgbtGreen = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1);
                gy_rgbtBlue = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1);
                gy_rgbtRed = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1);
            }
            
            // Corner bottom-right
            else if (i == height - 1 && j == width - 1)
            {
                // Gx compute  
                gx_rgbtGreen = (image[i][j - 1].rgbtGreen * -2) + (image[i - 1][j - 1].rgbtGreen * -1);
                gx_rgbtBlue = (image[i][j - 1].rgbtBlue * -2) + (image[i - 1][j - 1].rgbtBlue * -1);
                gx_rgbtRed = (image[i][j - 1].rgbtRed * -2) + (image[i - 1][j - 1].rgbtRed * -1);
                
                // Gy compute
                gy_rgbtGreen = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2);
                gy_rgbtBlue = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2);
                gy_rgbtRed = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2);
            }
            
            // Other pixel in first column
            else if ((i != 0 && i != height - 1)  && j == 0)
            {
                // Gx compute
                gx_rgbtGreen = image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                gx_rgbtBlue = image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                gx_rgbtRed = image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                
                // Gy compute
                gy_rgbtGreen = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                gy_rgbtBlue = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;
                gy_rgbtRed = image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
            }
            
            // Other pixels in last column
            else if ((i != 0 && i != height - 1)  && j == width - 1)
            {
                // Gx compute
                gx_rgbtGreen = image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1 + image[i - 1][j - 1].rgbtGreen * -1;
                gx_rgbtBlue = image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1 + image[i - 1][j - 1].rgbtBlue * -1;
                gx_rgbtRed = image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1 + image[i - 1][j - 1].rgbtRed * -1;
                
                // Gy compute
                gy_rgbtGreen = image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen * 2;
                gy_rgbtBlue = image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue * 2;
                gy_rgbtRed = image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed * 2;

            }
            
            // Other pixels in first row
            else if (i == 0 && (j != 0 && j != width - 1))
            {
                // Gx compute
                gx_rgbtGreen = image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1;
                gx_rgbtBlue = image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1;
                gx_rgbtRed = image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1;
                
                // Gy compute
                gy_rgbtGreen = image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                gy_rgbtBlue = image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;
                gy_rgbtRed = image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
            }

            // Other pixels in last row
            else if (i == height - 1 && (j != 0 && j != width - 1))
            {
                // Gx compute
                gx_rgbtGreen = image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1;
                gx_rgbtBlue = image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1;
                gx_rgbtRed = image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1;
                
                // Gy compute
                gy_rgbtGreen = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j + 1].rgbtGreen * -1;
                gy_rgbtBlue = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j + 1].rgbtBlue * -1;
                gy_rgbtRed = image[i - 1][j].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j + 1].rgbtRed * -1;
            }

            // All other pixels
            else
            {
                // Gx compute
                gx_rgbtGreen = (image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j - 1].rgbtGreen * -2 + image[i][j].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j - 1].rgbtGreen * -1 + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1);
                gx_rgbtBlue = (image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j - 1].rgbtBlue * -2 + image[i][j].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j - 1].rgbtBlue * -1 + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1);
                gx_rgbtRed = (image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * 0 + image[i - 1][j + 1].rgbtRed * 1) + (image[i][j - 1].rgbtRed * -2 + image[i][j].rgbtRed * 0 + image[i][j + 1].rgbtRed * 2) + (image[i + 1][j - 1].rgbtRed * -1 + image[i + 1][j].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1);
                
                // Gy compute
                gy_rgbtGreen = (image[i - 1][j - 1].rgbtGreen * -1 + image[i][j - 1].rgbtGreen * 0 + image[i + 1][j - 1].rgbtGreen * 1) + (image[i - 1][j].rgbtGreen * -2 + image[i][j].rgbtGreen * 0 + image[i + 1][j].rgbtGreen * 2) + (image[i - 1][j + 1].rgbtGreen * -1 + image[i][j + 1].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1);
                gy_rgbtBlue = (image[i - 1][j - 1].rgbtBlue * -1 + image[i][j - 1].rgbtBlue * 0 + image[i + 1][j - 1].rgbtBlue * 1) + (image[i - 1][j].rgbtBlue * -2 + image[i][j].rgbtBlue * 0 + image[i + 1][j].rgbtBlue * 2) + (image[i - 1][j + 1].rgbtBlue * -1 + image[i][j + 1].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1);
                gy_rgbtRed = (image[i - 1][j - 1].rgbtRed * -1 + image[i][j - 1].rgbtRed * 0 + image[i + 1][j - 1].rgbtRed * 1) + (image[i - 1][j].rgbtRed * -2 + image[i][j].rgbtRed * 0 + image[i + 1][j].rgbtRed * 2) + (image[i - 1][j + 1].rgbtRed * -1 + image[i][j + 1].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1);

            }
          
            // Compute final value = √(Gx^2 + Gy^2)
            edgesgreen = round(sqrt(pow(gx_rgbtGreen, 2) + pow(gy_rgbtGreen, 2)));
            edgesblue = round(sqrt(pow(gx_rgbtBlue, 2) + pow(gy_rgbtBlue, 2)));
            edgesred = round(sqrt(pow(gx_rgbtRed, 2) + pow(gy_rgbtRed, 2)));
            
            // Check and correct in case the value exceeds the 0-255 limits
            if (edgesgreen < 0)
            {
                edgesgreen = 0;
            }
            else if (edgesgreen > 255)
            {
                edgesgreen = 255;
            }
            
            if (edgesblue < 0)
            {
                edgesblue = 0;
            }
            else if (edgesblue > 255)
            {
                edgesblue = 255;
            }
            
            if (edgesred < 0)
            {
                edgesred = 0;
            }
            else if (edgesred > 255)
            {
                edgesred = 255;
            }
            
            // Assign value to array edge
            edges[i][j].rgbtGreen = edgesgreen;
            edges[i][j].rgbtBlue = edgesblue;
            edges[i][j].rgbtRed = edgesred;
            
        }
    }

    // Iterate around each row
    for (int k = 0; k < height; k++)
    {
        // Iterate around each column and assign the value of reflect array to image array
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtBlue = edges[k][l].rgbtBlue;
            image[k][l].rgbtGreen = edges[k][l].rgbtGreen;
            image[k][l].rgbtRed = edges[k][l].rgbtRed;
        }
    }
    return;
}
