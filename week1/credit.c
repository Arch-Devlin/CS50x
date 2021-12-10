#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for credit card number

    long number = get_long("Credit card number: ");

    if (number < 100000000000)
    {
        printf("INVALID\n");
        return 0;
    }

    else if (number > 100000000000)
        // calculate checksum
    {
        //Usefull variables for adding every second digit from the second last and oubling ect
        int n = number % 10;
        long Nn = number - n;
        long N = Nn / 10;

        int a = 0;
        int b = 0;
        int c = 0;
        int y = 0;
        
        //Usefull variables for adding every digit from the last
        long Nu = number;
        int d = 0;
        int x = 0;
        //Double and add the digits of every second digit starting from the second last
        for (N = Nn / 10; N > 0; N = ((N - (N % 100)) / 100))
        {
            a = (N % 10) * 2;
            if (a > 9)
            {
                b = a % 10;
                c = (a - b) / 10;
                y = y + b + c;
            }
            else if (a <= 9)
            {
                y = a + y;
            }
        }

        //Add every digit from the last
        for (Nu = number; Nu > 0; Nu = ((Nu - (Nu % 100)) / 100))
        {
            d = Nu % 10;

            x = d + x;
        }
        
        // Checking sum
        int sum = x + y;
        int Csum = sum  % 10;
        if (Csum != 0)
        {
            printf("INVALID\n");
            return 0;
        }
        else if (Csum == 0)
        {
            // determinint which card type
            int L2 = 0;
            for (Nu = number; Nu > 10; Nu = ((Nu - (Nu % 10)) / 10))
            {
                L2 = Nu;
            }
            if (39 < L2 && L2 < 50)
            {
                printf("VISA\n");
                return 0;
            }
            else if (50 < L2 && L2 < 56)
            {
                printf("MASTERCARD\n");
                return 0;
            }
            else if (L2 == 34 || L2 == 37)
            {
                printf("AMEX\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
    }
}
