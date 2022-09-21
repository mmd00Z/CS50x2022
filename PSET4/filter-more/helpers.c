#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
} Position;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayscale_pixel_coler = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0) + 0.5;
            image[i][j].rgbtBlue = grayscale_pixel_coler;
            image[i][j].rgbtGreen = grayscale_pixel_coler;
            image[i][j].rgbtRed = grayscale_pixel_coler;
        }
    }
}

// This function swaps values pointed by a and b
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - j - 1]);
        }
    }
}

// get the average value of the neighbor pixels
void get_neighbors_average(RGBTRIPLE *self, Position self_pos, int h, int w, RGBTRIPLE image[h][w])
{
    int sum_r = 0, sum_g = 0, sum_b = 0;
    ++self_pos.x;
    ++self_pos.y;
    float n = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (self_pos.y - i > -1 && self_pos.y - i < h && self_pos.x - j > -1 && self_pos.x - j < w)
            {
                sum_b += image[self_pos.y - i][self_pos.x - j].rgbtBlue;
                sum_g += image[self_pos.y - i][self_pos.x - j].rgbtGreen;
                sum_r += image[self_pos.y - i][self_pos.x - j].rgbtRed;
                n++;
            }
        }
    }
    (*self).rgbtBlue = (int)((sum_b / n) + 0.5);
    (*self).rgbtGreen = (int)((sum_g / n) + 0.5);
    (*self).rgbtRed = (int)((sum_r / n) + 0.5);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Position self_pos;
            self_pos.y = i;
            self_pos.x = j;
            get_neighbors_average(&new_image[i][j], self_pos, height, width, image);
        }
    }
    memcpy(image, new_image, sizeof(new_image));
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Position self_pos;
            self_pos.y = y + 1;
            self_pos.x = x + 1;
            int r_gx = 0, g_gx = 0, b_gx = 0;
            int r_gy = 0, g_gy = 0, b_gy = 0;
            for (int i = 0; i < 3; i++)
            {
                b_gx += (self_pos.y - i > -1 && self_pos.y - i < height
                         && x - 1 > -1) ? (image[self_pos.y - i][x - 1].rgbtBlue * ((i == 1) ? -2 : -1)) : 0;
                b_gx += (self_pos.y - i > -1 && self_pos.y - i < height
                         && x + 1 < width) ? (image[self_pos.y - i][x + 1].rgbtBlue * ((i == 1) ? +2 : +1)) : 0;
                g_gx += (self_pos.y - i > -1 && self_pos.y - i < height
                         && x - 1 > -1) ? (image[self_pos.y - i][x - 1].rgbtGreen * ((i == 1) ? -2 : -1)) : 0;
                g_gx += (self_pos.y - i > -1 && self_pos.y - i < height
                         && x + 1 < width) ? (image[self_pos.y - i][x + 1].rgbtGreen * ((i == 1) ? +2 : +1)) : 0;
                r_gx += (self_pos.y - i > -1 && self_pos.y - i < height
                         && x - 1 > -1) ? (image[self_pos.y - i][x - 1].rgbtRed * ((i == 1) ? -2 : -1)) : 0;
                r_gx += (self_pos.y - i > -1 && self_pos.y - i < height
                         && x + 1 < width) ? (image[self_pos.y - i][x + 1].rgbtRed * ((i == 1) ? +2 : +1)) : 0;

                b_gy += (self_pos.x - i > -1 && self_pos.x - i < height
                         && y - 1 > -1) ? (image[y - 1][self_pos.x - i].rgbtBlue * ((i == 1) ? -2 : -1)) : 0;
                b_gy += (self_pos.x - i > -1 && self_pos.x - i < height
                         && y + 1 < width) ? (image[y + 1][self_pos.x - i].rgbtBlue * ((i == 1) ? +2 : +1)) : 0;
                g_gy += (self_pos.x - i > -1 && self_pos.x - i < height
                         && y - 1 > -1) ? (image[y - 1][self_pos.x - i].rgbtGreen * ((i == 1) ? -2 : -1)) : 0;
                g_gy += (self_pos.x - i > -1 && self_pos.x - i < height
                         && y + 1 < width) ? (image[y + 1][self_pos.x - i].rgbtGreen * ((i == 1) ? +2 : +1)) : 0;
                r_gy += (self_pos.x - i > -1 && self_pos.x - i < height
                         && y - 1 > -1) ? (image[y - 1][self_pos.x - i].rgbtRed * ((i == 1) ? -2 : -1)) : 0;
                r_gy += (self_pos.x - i > -1 && self_pos.x - i < height
                         && y + 1 < width) ? (image[y + 1][self_pos.x - i].rgbtRed * ((i == 1) ? +2 : +1)) : 0;
            }
            new_image[y][x].rgbtBlue = (sqrt(b_gx * b_gx + b_gy * b_gy) >= 255) ? 255 : sqrt(b_gx * b_gx + b_gy * b_gy) + 0.5;
            new_image[y][x].rgbtGreen = (sqrt(g_gx * g_gx + g_gy * g_gy) >= 255) ? 255 : sqrt(g_gx * g_gx + g_gy * g_gy) + 0.5;
            new_image[y][x].rgbtRed = (sqrt(r_gx * r_gx + r_gy * r_gy) >= 255) ? 255 : sqrt(r_gx * r_gx + r_gy * r_gy) + 0.5;
        }
    }
    memcpy(image, new_image, sizeof(new_image));
}
