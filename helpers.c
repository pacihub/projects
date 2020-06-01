#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++)
    {

        float average;

        for(int j=0; j<width; j++)
        {

            average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3.00;
int ave = round(average);

            image[i][j].rgbtRed = ave;
            image[i][j].rgbtBlue = ave;
            image[i][j].rgbtGreen = ave;
        }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    
    for(int i=0; i<height; i++)
    {

float Rf,Gf,Bf;
        for(int j=0; j<width; j++)
        {

            Rf = 0.393*image[i][j].rgbtRed + 0.189*image[i][j].rgbtBlue + 0.769*image[i][j].rgbtGreen;
            Gf = 0.349*image[i][j].rgbtRed + 0.168*image[i][j].rgbtBlue + 0.686*image[i][j].rgbtGreen;
            Bf = 0.272*image[i][j].rgbtRed + 0.131*image[i][j].rgbtBlue + 0.534*image[i][j].rgbtGreen;
            
            int R = round(Rf);
            int G = round(Gf);
            int B = round(Bf);
            
            if(R>255)
            {
                R = 255;
            }
             if(G>255)
            {
                G = 255;
            }
            if(B>255)
            {
                B = 255;
            }
            
            
            image[i][j].rgbtRed = R;
            image[i][j].rgbtBlue = B;
            image[i][j].rgbtGreen = G;
        }

    }
    
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
