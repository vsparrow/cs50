#include <cs50.h>
#include <stdio.h>

// a program that recreates  half-pyramids using hashes (#) for blocks.

int main(void)
{
    // prompt the user for the half-pyramids' heights, a non-negative integer no greater than 23
    int n;
    do
    {
        n = get_int("Enter a number from 0 - 23: ");
    }
    while (n < 0 || n > 23);

    // left-align the bottom-left corner of the left-hand half-pyramid with the left-hand edge of your terminal window.
    // gap of size 2 separating them

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (j - i >= 0)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("  ");

        for (int k = 0; k < n; k++)
        {
            if (k - i >= 0)
            {
                printf("#");
            }
        }

        printf("\n");
    }

}