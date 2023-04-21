#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);

int main(void)
{
    // prompt the user for a string of text using get_string.
    string text = get_string("Text: ");
    count_letters(text);

}

int count_letters(string text)
{
    int l_count = 0;
    int w_count = 1;
    int s_count = 0;
    int i;

    // count words (a word is any sequence of characters separated by spaces)
    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            w_count++;
            // printf("CHAR: %c\n", text[i]);
        }
    // count sentences (any occurrence of a period, exclamation point, or question mark indicates the end of a sentence)
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s_count++;
        }
    // count letters (a letter is any lowercase character from a to z or any uppercase character from A to Z)
        else if (isalpha(text[i]))
        {
            l_count++;
        }
    }


    // printf("LETTERS: %i\n", l_count);
    // printf("WORDS: %i\n", w_count);
    // printf("SENTENCES: %i\n", s_count);
    // printf("i: %i\n", i);
    return 0;
}



    // print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer

    // if index number is 16 or higher, output "Grade 16+"

    // if index number is less than 1, output "Before Grade 1"