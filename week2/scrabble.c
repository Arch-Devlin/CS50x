#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0};

//functions
int compute_score(string word);

//variales



int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int y = 0;
    int points = 0;
    {
        string s = word;

        printf("Output:\n");

        for (int i = 0, n = strlen(s); i < n; i++)
        {
            int x = 0;
            int z = 0;

            if (s[i] >= 'a' && s[i] <= 'z')
            {
                x = s[i] - 32;

                printf("%c\n", x);

                z = x - 65;

                printf("%i\n", z);

            }
            else if (s[i] >= 'A' && s[i] <= 'Z')
            {
                x = s[i];

                printf("%c\n", x);

                z = x - 65;

                printf("%i\n", z);

            }
            else
            {
                printf("Punctuation\n");
                
                z = 27;
            }



            printf("%i\n", POINTS[z]);

            points = points + POINTS[z];

            printf("%i\n", points);


        }
    }


    return points;
}
