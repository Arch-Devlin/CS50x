#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    // TODO: Prompt for change due

    float due;
    do
    {
        due = get_float("Change owed:");
    }
    while (due < 0);

    int cents = round(due * 100);

    printf("%i cents due\n", cents);

    int D = 0;

    int Q = 0;

    int N = 0;

    int C = 0;
    {
        if (cents >= 25)

            do // GIVE quarters
            {
                cents = cents - 25;

                Q++;

            }
            while (cents >= 25);

        printf("%i quarters\n", Q); // check q
        {
            if (cents >= 10 && cents < 25)

                do// GIVE dimes
                {
                    cents = cents - 10;

                    D++;

                }
                while (cents >= 10 && cents < 25);


            printf("%i dimes\n", D); // check d
            {
                if (cents >= 5 && cents < 10)

                    do// GIVE nickels
                    {
                        cents = cents - 5;

                        N++;

                    }
                    while (cents >= 5 && cents < 10);


                printf("%i nickels\n", N); // check n
                {
                    if (cents >= 1 && cents < 5)

                        do// GIVE nickels
                        {
                            cents = cents - 1;

                            C++;

                        }
                        while (cents >= 1 && cents < 5);


                    printf("%i cents\n", C); // check n
                }
            }
        }
    }
    // calc total coins

    int T = Q + D + N + C;

    printf("%i\n", T); // check t

}
