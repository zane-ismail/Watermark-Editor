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
    for (int i = 0; i < candidate_count; i++)
    {
        // if name matches one of the candidates then update that candidate’s vote total to account for the new vote
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            // vote function should return true to indicate a successful ballot
            return true;
        }
    }
    // if name does not match any of the candidates, no vote totals should change, vote function should return false
    return false;
}

void print_winner(void)
{
    // TODO
    int max_votes = 0;
    // iterate through candidates to find who has the most votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            // set the max vote integer as the highest vote count
            max_votes = candidates[i].votes;
        }
    }
    // iterate through candidates to find the ones with the highest number of votes
    for (int j = 0; j < candidate_count; j++)
    {
        // if election is a tie output the names of each of the winning candidates, each on a separate line.
        if (candidates[j].votes == max_votes)
        {
            // print out the name of the candidate who received the most votes in the election, and then print a newline.
            printf("%s\n", candidates[j].name);
            candidates[j].votes = 0;
        }
    }
}
