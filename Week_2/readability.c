#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int get_letters(string text);

int get_words(string text);

int get_sentences(string text);

int main(void)
{
    // Prompts the user for a text to be graded
    string text = get_string("Text: ");
    //Saves the number of letters, words and sentences in integers
    int letters = get_letters(text);
    int words = get_words(text);
    int sentences = get_sentences(text);

    //Calculates the average number of letters per 100 words
    float L = (float) letters / words * 100;
    //Calculates the average number of sentences per 100 words
    float S = (float) sentences / words * 100;
    //Computes the Coleman-Liau index of the text
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    //Prints out the grade of the text according to the formula
    while (true)
    {
        if (index >= 16)
        {
            printf("Grade 16+\n");
            return false;
        }
        else if (index < 1)
        {
            printf("Before Grade 1\n");
            return false;
        }
        else
        {
            printf("Grade %i\n", index);
            return false;
        }
    }
}

// Calculates the number of letters in the text
int get_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Calculates the number of words in the text
int get_words(string text)
{
    int words = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words;
}

// Calculates the number of sentences in the text
int get_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.')
        {
            sentences++;
        }
        else if (text[i] == '!')
        {
            sentences++;
        }
        else if (text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}