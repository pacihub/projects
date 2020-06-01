#include "helpers.h"
#include<math.h>

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

            int R = round(Rf); int G = round(Gf); int B = round(Bf);

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
    
    //here i define a second identical image. a copy. i will swap pixels
    RGBTRIPLE image2[height][width];

//with these for loops i assign all pixels from original image to image2 in a mirror fashio.
    for(int i=0; i<height; i++)
    {

        for(int j=0; j<width; j++)
        {
//i take the width as a factor here. for example index0 from image will appear as index width-1-0. we start counting from 0, don't forget. if width =5, then last index will be 4. that's why width-1
            image2[i][j].rgbtRed = image[i][width-1-j].rgbtRed ;
            image2[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue ;
            image2[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen ;
        }

    }
//here i assign every pixel from 2 to 1. because my outpout is image and not image2
   for(int i = 0; i<height; i++)
  {
       for(int j=0; j<width; j++)
       {
           image[i][j].rgbtRed = image2[i][j].rgbtRed;
           image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
           image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
       }
   }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
