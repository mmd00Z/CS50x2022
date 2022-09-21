#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string str = get_string("Text: ");
    int n_letters = 0, n_words = 1, n_sentences = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            n_words++;
        }
        else if (str[i] == '.' || str[i] == '?' || str[i] == '!')
        {
            n_sentences++;
        }
        if (isalpha(str[i]))
        {
            n_letters++;
        }
    }
    double L = (100.0 * n_letters) / n_words;
    double S = (100.0 * n_sentences) / n_words;
    int readablity = (0.0588 * L - 0.296 * S - 15.8) + 0.5;
    if (readablity >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (readablity < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", readablity);
    }
}