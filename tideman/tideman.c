#include <cs50.h>
#include <string.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // the function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // update the ranks array to indicate that the voter has the candidate as their rank preference
            ranks[rank] = i;
            // function should return true if the rank was successfully recorded
            return true;
        }
    }
    // otherwise (if, for instance, name is not the name of one of the candidates).
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // the function is called once for each voter
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count-1; j++)
            // update the global preferences array to add the current voter’s preferences
            {
                if (i != ranks[0] && i != ranks[j])
                {
                    preferences[ranks[j]][i]++;
                }
                // printf("%i: ", i);
                // printf("%i:  ", j);
                // printf("%i\n", preferences[i][ranks[i]]);
            }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // add all pairs of candidates where one candidate is preferred to the pairs array
    // printf("A/A: %i\n", preferences[0][0]);
    // printf("A/B: %i\n", preferences[0][1]);
    // printf("A/C: %i\n", preferences[0][2]);
    // printf("B/A: %i\n", preferences[1][0]);
    // printf("B/B: %i\n", preferences[1][1]);
    // printf("B/C: %i\n", preferences[1][2]);
    // printf("C/A: %i\n", preferences[2][0]);
    // printf("C/B: %i\n", preferences[2][1]);
    // printf("C/C: %i\n", preferences[2][2]);
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // a pair of candidates who are tied (one is not preferred over the other) should not be added to the array
            if (preferences[i][j] != 0 && i != j && preferences[i][j] != preferences[j][i])
            {
                // The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive)
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // update the global variable pair_count to be the number of pairs of candidates
                printf("Winner: %d\n", pairs[pair_count].winner);
                printf("Lose: %d\n", pairs[pair_count].loser);
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max_pair = 0;
    // TODO
    // sort the pairs array in decreasing order of strength of victory
    // strength of victory is defined to be the number of voters who prefer the preferred candidate.
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (pairs[i].winner > pairs[j].winner)
            {
                max_pair = pairs[i].winner;
                pairs[i].winner = max_pair;
            }
        }
    }
    // if multiple pairs have the same strength of victory, you may assume that the order does not matter.
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (pairs[i].winner != pairs[j].winner)
            {
                locked[i][j] = true;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // print out the name of the candidate who is the source of the graph (assume there will not be more than one source.)
    printf("%s\n", candidates[pairs[0].winner]);
    return;
}