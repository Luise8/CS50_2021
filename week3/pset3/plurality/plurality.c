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
    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        
        // Check if the vote corresponds to i candidate, if correct increase candidates[i].votes and return true
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    
    // In case of not corroesponds, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Bubble sort
    int count; // Variable to quit in case of not change
    int record_value; // Record value of first element of array for change the next element
    string record_name; // Record name of first element of array
    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        count = 0;
        // Loop over all candidates - 1
        for (int j = 0; j < (candidate_count - 1); j++)
        {
            
            // If the first element is greater than the second, then swap them
            if (candidates[j].votes > candidates[j + 1].votes) 
            {
                record_value = candidates[j].votes; // Temporarily stores the value of the first element
                record_name = candidates[j].name;   // Temporarily stores the name of the first element
                candidates[j].votes = candidates[j + 1].votes; // Apply the first change.
                candidates[j].name = candidates[j + 1].name;   // Apply the first change.
                candidates[j + 1].votes = record_value;        // Apply the second change.
                candidates[j + 1].name = record_name;          // Apply the second change.    
                count++; 
            }
        }
        
        // In case of not change, increase var i to candidate_count for quit loop
        if (count == 0) 
        {
            i = candidate_count;
        }
    }
    
    // Check if there are one or more winners.
    if (candidates[candidate_count - 1].votes != candidates[candidate_count - 2].votes) // In case one winner, print this
    {
        printf("%s\n", candidates[candidate_count - 1].name);
    }
    else // In case of several winners, print these
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[candidate_count - 1].votes == candidates[i].votes)
            {
                printf("%s\n", candidates[i].name);
            }
        }
    }

}
