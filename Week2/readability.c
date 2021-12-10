#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Functions
int compute_letters(string texts);
int compute_words(string texts);
int compute_sentences(string texts);

int main(void)
{
    // Get input text
    string text = get_string("Text: ");
    // count letters
    float letters = compute_letters(text);
    printf("%f Letter(s)\n", letters);
    // count spaces + 1
    float words = compute_words(text);
    printf("%f Word(s)\n", words);
    // cont sentences
    float sentences = compute_sentences(text);
    printf("%f Sentence(s)\n", sentences);
    // calculate average number of letters per 100 words in the text (L)
    float L = 100 * (letters / words);
    printf("L = %f\n", L);
    // calculate the average number of sentences per 100 words (S)
    float S = 100 * (sentences / words);
    printf("S = %f\n", S);
    // calculate Coleman-Liau index
    float index = ((0.0588 * L) - (0.296 * S) - (15.8));
    printf("Coleman-Liau index = %f\n", index);
    // round Coleman-Liau index
    int CLI = round(index); // CS50 Manual Library
    printf("CLI = %i\n", CLI);
    // Final Output
    if (CLI < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (CLI >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", CLI);
    }

}
// Counting letters
int compute_letters(string texts)
{
    int letter = 0;
    {
        string s = texts;

        for (int i = 0, n = strlen(s); i < n; i++) // CS50 Manual Library
        {
            if (isalpha(s[i])) // CS50 Manual Library
            {
                letter++;
            }
        }
    }
    return letter;
}
//Counting spaces + 1
int compute_words(string texts)
{
    int word = 1;
    {
        string s = texts;

        for (int i = 0, n = strlen(s); i < n; i++) // CS50 Manual Library
        {
            if (isspace(s[i])) // CS50 Manual Library
            {
                word++;
            }
        }
    }
    return word;
}
// counting  . + ? + !
int compute_sentences(string texts)
{
    int sentence = 0;
    {
        string s = texts;

        for (int i = 0, n = strlen(s); i < n; i++) // CS50 Manual Library
        {
            if (s[i] == '.' || s[i] == '!' || s[i] == '?')
            {
                sentence++;
            }
        }
    }
    return sentence;
}
