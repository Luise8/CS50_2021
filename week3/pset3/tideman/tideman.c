#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
int check_cycle(int indice, int pair_i_max, pair pairs1[], bool locked1[][MAX]);

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
    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the vote corresponds to i candidate,
        // if correct store the index of the candidate in ranks[rank] and return true
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If not corresponds with anybody, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop over all ranks or candidate_count
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop over all candidates for each ranks[i]
        for (int j = 0; j < candidate_count; j++)
        {
            // If rank[i] matches candidate j, start the next loop
            if (ranks[i] == j)
            {
                // Loop to record the preferences of ranks[i]
                // over the rest of the candidates
                for (int k = 0; k < candidate_count; k++)
                {
                    if (ranks[i] != ranks[k] && i <= k)
                    {
                        preferences[j][ranks[k]]++;
                    }
                }
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop for comparing each pair against another pairs
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }

    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort
    int temp_winner; // Record winner of first element of array
    int temp_loser; // Record loser of first element of array
    int count = 0;  // // Variable to quit in case of not change
    // Loop over all pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Loop over all pairs - 1, startin with the last and decresing up the first
        for (int j = pair_count - 1; j > 0; j--)
        {
            //   // If the last element is greater than the last - 1, then swap them
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[j - 1].winner][pairs[j - 1].loser])
            {
                temp_winner = pairs[j].winner; // Temporarily stores the value of the first element
                temp_loser = pairs[j].loser;   // Temporarily stores the name of the first element
                pairs[j].winner = pairs[j - 1].winner; // Apply the first change.
                pairs[j].loser = pairs[j - 1].loser;  // Apply the first change.
                pairs[j - 1].winner = temp_winner;    // Apply the second change.
                pairs[j - 1].loser = temp_loser;     // Apply the second change.
                count++;
            }
        }
        // In case of not change, increase var i to candidate_count for quit loop
        if (count == 0)
        {
            i = pair_count;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Varible that will serve to check if there is a cycle.
    int checking = 0;
    
    // Loop over all pairs
    for (int i = 0; i < pair_count; i++)
    {
        
        // Reset checking in each iteration and then check if there is a cycle with the current pair, 
        // invoking the check_cycle and saving the result in checking
        checking = 0;
        checking = check_cycle(i, i, pairs, locked);
        
        // Evaluates if there is a cycle, looking for a match between checking and the current i,and also a non-zero number in i.
        // The latter is because in the pair 0 during the first round the result of the check_cycle function will coincide, 
        // then it will be the same checking and the variable i during this first round, 
        // although this will never mean a loop because with a single pair you cannot create a cycle .
        if (checking == i && i > 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = false; // Cycle
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true; // Don't cycle
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        bool loser = false; // Bool to check if it i was loser in the locked array
        
        // Loop over all candidates to check loser
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) // Check if it is blocked which candidate j beats candidate i
            {
                loser = true;
                break;
            }
        }
        
        bool winner = false; // Bool to check if it i was winner in the locked array
        
        // Loop over all candidates to check winner
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[i][k]) // Check if it is blocked which candidate i beats candidate k
            {
                winner = true;
                break;
            }
        }
        
        // If he didn't lose and was winner in the locked array, is the source
        if (loser == false && pair_count != 0 && winner == true) 
        {
            printf("%s\n", candidates[i]);
        }
    }
}

// Check if ith pair create a cycle. Return number of ith if it create a cycle, on the contrary return 0. Recursive function.
int check_cycle(int indice, int pair_i_max, pair pairs1[], bool locked1[][MAX])
{   
    // Variable that will store the number that will indicate whether the pair creates a loop or not.
    int check = 0;
    
    // Loop over all candidates up to the current position of i (pair_i_max)
    for (int i = 0; i <= pair_i_max; i++)
    {
        
        // Check if the loser is the winner of any pair up to the pair_i_max in the locked array
        if (pairs1[indice].loser == pairs1[i].winner && (locked1[pairs[i].winner][pairs[i].loser] == true || i == pair_i_max))
        {
            
            // Check if i is equal to pair_max_i, that is, the previous loser coincides with the current winner of i, 
            // which is a cycle because it started from the loser pair_i_max and returns to the winner of pair_i_max
            if (i == pair_i_max)
            {
                // In this case check will take this value and break the loop.
                check = i;
                break;
            }
            else
            {
                // On the contrary, the check continues with the new loser of the current loser of pair i, entered as an index. 
                // (This is the only change to the data entered in the function). This is the recursion. And save in var check.
                check = check_cycle(i, pair_i_max, pairs1, locked1);
                // Now, Now, the previous check again.
                if (check == pair_i_max)
                {
                    break;
                }
            }
        }
    }
    
    // Once the loop is finished. The result will be some nonzero number if there is a loop.
    return check;
}
