#include <cs50.h>
#include <stdio.h>

int main(void)
// get hight
{
    int h;
    do
    {
        h = get_int(" What hight is the pyramid? \n");
    }
    while (1 > h || h > 8);

    int H = h;
    // print
    for (H = h; H > 0; H--)
    {
        // print spaces
        for (int w = H - 1; w > 0; w--)
        {
            printf(" ");

        }

        // print #
        for (int hash = H; hash <= h; hash++)
        {
            printf("#");
        }

        //mddle
        printf("  ");
        // second half #
        for (int hash = H; hash <= h; hash++)
        {
            printf("#");
        }

        printf("\n");
    }
}
