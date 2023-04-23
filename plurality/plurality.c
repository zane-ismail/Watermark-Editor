#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // vote takes a single argument, a string called name, representing the name of the candidate who was voted for

    // If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote
    for (int i = 0; i <= MAX; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            // The vote function in this case should return true to indicate a successful ballot
            return true;
        }
        // If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return false to indicate an invalid ballot
    }
    // You may assume that no two candidates will have the same name
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // The function should print out the name of the candidate who received the most votes in the election, and then print a newline.
    string winner_a;
    string winner_b;
    // Find max votes
    int max = candidates[0].votes;
    for (int i = 0; i <= MAX; i++)
    {
        for (int j = 0; j <= MAX; j++)
        {
            if (candidates[j].votes > max)
            {
                winner_a = candidates[j].name;
                max = candidates[j].votes;
                printf("%s\n", winner_a);
            }
            // else if (candidates[j].votes == max)
            // {
            //     winner_b = winner_a;
            //     winner_a = candidates[j].name;
            //     max = candidates[j].votes;
            //     printf("%s ", winner_a);
            //     printf("%s\n", winner_b);
            // }
            else
            {
                winner_a = candidates[0].name;
                printf("%s\n", winner_a);
            }
        }
    }

    // It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes.
    // In that case, you should output the names of each of the winning candidates, each on a separate line.
    return;
}