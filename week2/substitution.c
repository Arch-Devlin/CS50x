#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//Functions
int check_key1(string key);
int check_key2(string key);

int main(int argc, string argv[])
{
    //check KEY
    int key_text = argc - 1;
    string KEY = argv[key_text];

    int check1 = check_key1(KEY);
    int check2 = check_key2(KEY);

    int check = check1 + check2;
    if (check > 0)
    {
        return 1;
    }
    else if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //The rest
    else
    {
        string plaintext = get_string("Plaintext: ");

        string P = plaintext;

        printf("ciphertext: ");

        for (int i = 0, n = strlen(P); i < n; i++)
        {
            char now = P[i];
            if (islower(now))//for lower case characters //CS50 Manual
            {
                int x = now - 97;
                char C = KEY[x];
                printf("%c", tolower(C));//CS50 Manual
            }
            else if (isupper(now))//for upper case characters //CS50 Manual
            {
                int x = now - 65;
                char C = KEY[x];
                printf("%c", toupper(C));//CS50 Manual
            }
            else//for everything else
            {
                printf("%c", now);
            }
        }
        printf("\n");
        return 0;//End
    }


}

//Check key lenght and characters
int check_key1(string key)
{
    string K = key;
    int isalpha_check_true = 0;
    //Check key lenght
    if (strlen(K) != 26)//CS50 Manual
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Check if only alphabetical characters
    else if (strlen(K) == 26)//CS50 Manual
        for (int i = 0, n = strlen(K); i < n; i++)//CS50 Manual
        {
            if (isalpha(K[i]) == 0)//CS50 Manual
            {
                printf("Key must contain only alphabetical characters.\n");
                return 1;
            }
        }
    return 0;
}

//Check for duplicate characters
int check_key2(string key)
{
    int dupe = 0;
    string K = key;

    for (int o = 0, m = strlen(K); o < m; o++)//CS50 Manual
    {
        for (int x = 0, p = strlen(K); x < p; x++)//CS50 Manual
        {
            if (K[o] == K[x])
            {
                dupe++;
            }
        }
        if (dupe > 26)
        {
            printf("Key must contain only 1 of each character.\n");
            return 1;
        }
    }
    return 0;
}
