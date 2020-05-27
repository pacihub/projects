#include <cs50.h>
#include <stdio.h>
#include<string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            //for vote we need 3 for loops. 2 for the rectangle (2D array) Y axis (voter_count) and X axis (candidate count).
            //for every square in this 2D array, we need the 3rd FOR loop to iterate through candidate names in memory (candidates[i].names) and compares the value to the typed VOTE
            //3rd loop is inside the vote function
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

//this is just for me to see how preferences get assigned in the 2D array. Check only the first 3 preferences for the 1st voter.

// printf("%i\n", preferences[0][0]);
// printf("%i\n", preferences[0][1]);
// printf("%i\n", preferences[0][2]);
        printf("\n");

    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();
   
   //this is just for me to see how tabulate function counts the number of votes, especially how it changes depending on if there is a 'break' in the loop.
   // printf("%s %i\n",candidates[0].name, candidates[0].votes);
    //printf("%s %i\n",candidates[1].name, candidates[1].votes);
 
    //break; (this break here, if i include it, it won't go down, but somehow it executes the code correctly.???)


        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;

}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int k=0; k< candidate_count; k++)
        {
            if(strcmp(candidates[k].name, name)==0)
                {
                preferences[voter][rank] = k;
                return true;
                }
        }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for(int i = 0; i< voter_count; i++)
        {
            for(int j=0; j<candidate_count; j++)
             {
                 if(candidates[preferences[i][j]].eliminated == false)
                    {
                        candidates[preferences[i][j]].votes +=1;
//if this break is not here, the algo will loop through all the squares on the board and therefore add
// one vote to every candidate. Meaning all candidates will end up with the same number of votes.
// try with and without the break to see difference with printfs for the first few candidates.
//the break stops the function right after the condition is met. meaning only one candidate will get the vote on the same row.
                break;
                    }
             }

        }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO

    for (int i=0; i<candidate_count; i++)
        {
            if(candidates[i].votes > (voter_count/2))
                {
                printf("Winner is: %s\n",candidates[i].name);
                return true;
                }
        }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
 int min = 101;
        for(int i = 0; i< candidate_count; i++)
        {
            if(candidates[i].votes < min)
            {
                if(!candidates[i].eliminated)
                {
                    min = candidates[i].votes;
                }
            }

        }

//returning min, because the next function will use that value. so we gotta feed it
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i<candidate_count;i++)
    {
        if((candidates[i].eliminated == false) && (candidates[i].votes != min))
            {
                return false;
            }

    }

    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i<candidate_count;i++)
        {
            if(candidates[i].votes == min)
                {
                    candidates[i].eliminated = true;
                }
        }

    return;
}
