#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // prompt the user for a string of text using get_string.
    string text = get_string("Text: ");
    // count_letters(text);
    // count_words(text);
    // count_sentences(text);

    int j = 1;
    for (int i = 0; text[i] != '\0'; i++)
        {
            if (count_words(text) % 100 == 0)
            {
                j++;
            }
        }

    // calculate average number of letters per 100 words
    float L = count_letters(text) / j;
    // calculate average number of sentences per 100 words
    float S = count_sentences(text)/ j;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("L: %f\n", L);
    printf("S: %f\n", S);
    printf("INDEX: %i\n", index);
}

int count_letters(string text)
{
    // count letters (a letter is any lowercase character from a to z or any uppercase character from A to Z)
    int l_count = 0;
    for (int i = 0; text[i] != '\0'; i++)
        {
            if (isalpha(text[i]))
            {
                l_count++;
            }
        }
    printf("%i letters\n", l_count);
    return l_count;
}

int count_words(string text)
{
    // count words (a word is any sequence of characters separated by spaces)
    int w_count = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            w_count++;
        }
    }
    printf("%i words\n", w_count);
    return w_count;
}

int count_sentences(string text)
{
    // count sentences (any occurrence of a period, exclamation point, or question mark indicates the end of a sentence)
    int s_count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s_count++;
        }
    }
    printf("%i sentences\n", s_count);
    return s_count;
}
    // print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer

    // if index number is 16 or higher, output "Grade 16+"

    // if index number is less than 1, output "Before Grade 1"