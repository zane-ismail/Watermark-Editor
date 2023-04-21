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
    // count letters
    int l_count = strlen(text);
    printf("LETTERS: %i\n", l_count);


    // count words
    int w_count = 
    return txt_len;
}




    // count sentences

    // a letter is any lowercase character from a to z or any uppercase character from A to Z

    // a word is any sequence of characters separated by spaces

    // any occurrence of a period, exclamation point, or question mark indicates the end of a sentence


    // print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer

    // if index number is 16 or higher, output "Grade 16+"

    // if index number is less than 1, output "Before Grade 1"