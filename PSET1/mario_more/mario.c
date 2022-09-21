#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("h: ");
    }
    while (!(h > 0 && h < 9));

    for (int i = 1; i <= h; i++)
    {
        // left half Mario's Pyramid
        for (int j = 0; j < h; j++)
        {
            printf((j < h - i) ? " " : "#");
        }
        printf("  ");
        // right half Mario's Pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}