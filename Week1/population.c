#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int initial;
    do
    {
        initial = get_int(" What is the initial population size? \n") ;
    }
    while (initial < 9) ;

    // TODO: Prompt for end size

    int final;
    do
    {
        final = get_int(" What is the intended final population size? \n") ;
    }
    while (final < initial) ;

    // TODO: Calculate number of years until we reach threshold

    // Establish year counter
    int year = 0;

    int x;

    x = initial;
    if (x < final)
        do
        {
            year++ ;

            x = x + (x / 3) - (x / 4) ;
        }
        while (x < final) ;

    // TODO: Print number of years

    if (final <= x)
    {
        printf("Years: %i", year);
    }

    else if (final == x)
    {
        printf("Years: %i", year);
    }

}
