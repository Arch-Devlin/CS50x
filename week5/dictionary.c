// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 18356;

// Hash table
node *table[N];

//establish size int s
int s = 0;

char cword[LENGTH];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int h = hash(word);

    node *cursor = table[h];
    node *check = cursor;

    do
    {
        check = cursor;

        if (strcasecmp(word, check->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    while (strcasecmp(word, check->word) != 0 && cursor != NULL);

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    const int num = 3;
    int hash = 0;
    int mx = 0;

    int factor[num];
    factor[0] = 678;
    factor[1] = 27;
    factor[2] = 1;

    int tmp[num];
    const char *new_word = word;

    for (int i = 0; i < num; i++)
    {
        char c = new_word[i];

        if (isalpha(c) == 0)
        {
            tmp[i] = (tolower(c) - 96);
        }
        else
        {
            tmp[i] = 0;
        }
    }

    for (int i = 0; i <= mx; i++)
    {
        hash = hash + (tmp[i] * factor[i]);
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // NULL table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dfile = fopen(dictionary, "r");
    if (dfile == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }
    else if (dfile != NULL)
    {
        while (fscanf(dfile, "%s", cword) != EOF)
        {
            node *tmp = malloc(sizeof(node));

            if (tmp == NULL)
            {
                unload();
                return false;
            }

            s++;

            strcpy(tmp->word, cword);
            tmp->next = NULL;

            int h = hash(tmp->word);

            if (table[h] == NULL)
            {
                table[h] = tmp;
            }
            else
            {
                tmp->next = table[h];
                table[h] = tmp;
            }
        }

    }

    fclose(dfile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return s;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp;

        if (cursor != NULL)
        {
            do
            {
                tmp = cursor;
                cursor = tmp->next;
                free(tmp);
            }
            while (cursor != NULL);
        }
    }
    return true;
}
