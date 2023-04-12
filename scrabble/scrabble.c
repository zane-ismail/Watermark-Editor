#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

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
        printf("%i ", score1);
        printf("wins!\n");
    }
    else
    {
        printf("%i ", score2);
        printf("wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int length = 0;
    int sum = 0;
    int score1 = 0;
    int score2 = 0;
    // Iterate through each letter and convert to integer
    for (length = 0; word[length] != '\0'; length++)
    {
        int letter = (word[length] - 97);
    // Create and tally a score
        int score1 = (POINTS[letter]);
        sum = (sum + score);
    }
    printf("%i\n", sum);
    return winner;
}
