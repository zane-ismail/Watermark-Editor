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
int locked_count;
int new_count;
int ORIGINAL;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool recursion(int w, int l);

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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // a pair of candidates who are tied (one is not preferred over the other) should not be added to the array
            if (preferences[i][j] > preferences[j][i])
            {
                // The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive)
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // printf("1Winner: %d\n", pairs[pair_count].loser);
                // printf("1Loser: %d\n", pairs[pair_count].winner);

                // update the global variable pair_count to be the number of pairs of candidates
                pair_count++;
            }
        }

    printf("Winner %i: ", i);
    printf("%i\n", pairs[i].winner);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // sort the pairs array in decreasing order of strength of victory
    // a pair of candidates who are tied (one is not preferred over the other) should not be added to the array
    int max_pair[pair_count];
    int max_count = 0;
    pair temp_max_count;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // strength of victory is defined to be the number of voters who prefer the preferred candidate.
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j+1].winner][pairs[j+1].loser])
            {
                printf("MC: %i\n", max_count);
                temp_max_count = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp_max_count;
            }
        }
        max_count = 0;
        printf("Winner %i: ", i);
        printf("%i\n", pairs[i].winner);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // first pair is locked
    locked[pairs[0].winner][pairs[0].loser] = true;
    // create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle
    for (int i = 1; i < pair_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // if the loser of the pair is the same as a winner of a previous pair
            if (pairs[i].loser == pairs[j].winner)
            {
                // check the pair is locked
                if (locked[pairs[j].winner][pairs[j].loser] == true)
                {
                    // check to see it's a cycle
                    ORIGINAL = pairs[i].winner;
                    if (recursion(pairs[j].winner, pairs[j].loser) == true)
                    {
                        // if it is a cycle, do not lock it
                        locked[pairs[i].winner][pairs[i].loser] = false;
                    }
                }
            }
        }
        // otherwise lock it
        locked[pairs[i].winner][pairs[i].loser] = true;
        locked_count++;
        new_count++;
    }
    return;
}

bool recursion(int w, int l)
{
    // check if original new pair winner is the same as a recurive pair loser
    if (l == ORIGINAL)
    {
        return true;
    }
    for (int i = 0; i < pair_count>; i++)
    {
    // check the previous is locked
        if (locked[pairs[i].winner][pairs[i].loser] == true)
        {
            // checks if new pair loser is the same as previous pair winner
            if (l == pairs[i].winner)
            {
                // checks if new pair winner is the same as previous pair loser
                recursion(pairs[i].loser, pairs[i].loser);
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // print out the name of the candidate who is the source of the graph (assume there will not be more than one source.)
    printf("%s\n", candidates[pairs[0].winner]);
    return;
}