#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"
/*
unsigned char * greying(unsigned char *image, int width, int height, int grey_channel, int channel)
{
    size_t image_size = width * height * channel;
    size_t grey_image_size = width * height * grey_channel;
 
    unsigned char *grey_image = malloc(grey_image_size);
    for(unsigned char *p = image, *pg = grey_image; p != image + image_size; p += channel, pg += grey_channel) {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
        if(channel == 4) {
            *(pg + 1) = *(p + 3);
        }
    }
    return grey_image;
}
*/
/*
unsigned char mask_image( unsigned char *image , int width , int height , int channel)
{
    for (int i = 0; i < height / 2; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            for ( int k = 0; k < channel ; k++)
            {
                image [i * width * channel + j * channel + k] = 0;
            }
        }
    }
}
*/
unsigned char * subtraction(unsigned char * fimage, unsigned char * bimage, unsigned char * rimage, int width, int height, int channel) 
{
    for (int i = 0; i < height ; i ++) 
    {
        for (int j = 0; j < width ; j ++)  
        {
            int diff = 0;
            for (int k = 0; k < channel ; k ++) 
            {
                diff += abs(fimage [ i * width * channel + j * channel + k ] -  bimage [ i * width * channel + j * channel + k ]);
            }
            if(diff < 170) 
            {
                for(int k = 0; k < channel ; k++) 
                {
                    fimage [ i * width * channel + j * channel + k ] = rimage [ i * width * channel + j * channel + k ];
                }
            }
        }
    }
}
int main ()
{
    int fwidth, fheight, fchannel;
    int bwidth, bheight, bchannel;
    int rwidth, rheight, rchannel;
    char fpath_img[] = "./images/foreground.png";
    char bpath_img[] = "./images/background.png";
    char rpath_img[] = "./images/weather_forecast.png";

    unsigned char * fimage = stbi_load(fpath_img, &fwidth, &fheight, &fchannel, 0);
    if (fimage == NULL)
    {
        printf("\nError in loading the image \n");
        exit(1);
    }
    printf ("Foreground image: Width = %dpx Height = %dpx Channel = %d\n", fwidth, fheight, fchannel);
    unsigned char * bimage = stbi_load(bpath_img, &bwidth, &bheight, &bchannel, 0);
    if (bimage == NULL)
    {
        printf("\nError in loading the image \n");
        exit(1);
    }
    printf ("Background image: Width = %dpx Height = %dpx Channel = %d\n", bwidth, bheight, bchannel);
    unsigned char * rimage = stbi_load(rpath_img, &rwidth, &rheight, &rchannel, 0);
    if (rimage == NULL)
    {
        printf("\nError in loading the image \n");
        exit(1);
    }
    printf ("Background image: Width = %dpx Height = %dpx Channel = %d\n", rwidth, rheight, rchannel);
    subtraction(fimage, bimage, rimage, rwidth, rheight, fchannel);
    stbi_write_png("./images/result.png",fwidth, fheight, fchannel, fimage, fwidth * fchannel);
    
}
