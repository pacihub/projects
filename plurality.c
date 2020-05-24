#include<stdio.h>
#include<cs50.h>
#include<string.h>


typedef struct
{
    string name;
    int votes;
}
candidate;

//global variables. VERY IMPORTANT. The functions VOTE and PRINT_WINNER see ONLY global variables. So all declarations they use
//must happen OUTSIDE of MAIN. I struggled for 30 mins with an error message about declaration...
#define MAX 9
int candidate_count;

candidate candidates[MAX];

void print_winner(void);
bool vote(string vote_name);

int main(int argc, string argv[])
{
    
   //setting the maximum elements in the array candidates to be 9. 
    
    
 //candidate count is argc-1, because the name of the program is also counted in argc
 candidate_count = argc-1;
 
 //initialize the votes of ever candidate to be 0 and also assigning names to the indexes in the string.
 for (int i=0; i<candidate_count; i++)
    {
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
    }
    
    //it is for me to check progress
    //printf("candidates: %i\n",candidate_count);
    //printf("candidate name1: %s \n", candidates[0].name);
    //printf("candidate name2: %s\n", candidates[1].name);
    
  int num_voters = get_int("Number of voters: ");
  
  //prompting the user to vote one (type name) time for each voter there is
  for (int j=0; j<num_voters; j++)
        {
            string vote_name = get_string("Vote: ");
            
    //with every prompting we run that function that I first wrote here directly but the pset guys asked me to call a function
    // the !vote is in case someone types a name that is not in the candidate list, then function returns false basically
                if(!vote(vote_name))
                 { 
                     printf("Invalid vote. \n");
                 }
           
        }
    
    
//the functions outside MAIN
    
    print_winner();
    
}
    //this function checks with every iteration of get string for vote if the name of ANY candidate (tht's why i run the for loop)
    //equals to a name typed in the vote. If it matches, then it increases the number of votes for this candidate.
        bool vote(string vote_name)
            {
                for(int i = 0; i<candidate_count; i++)
                {
                    if(strcmp(candidates[i].name, vote_name) == 0 )
                        {
                        candidates[i].votes++;
                        return true;
                         }
                }
                
                return false;
            }
    
    
    //just a print function that's why no inputs and no returns
    void print_winner(void)
    {
    
    int max_votes = 0;
    
    for (int k=0; k<candidate_count; k++)
        {
            if(candidates[k].votes >= max_votes)
            {
            max_votes = candidates[k].votes;
            }
        }
    
    for (int p=0; p < candidate_count; p++)
        {
            if(candidates[p].votes == max_votes)
            {
            printf("winner is: %s\n",candidates[p].name);
            }
        }
    
    
    
    //printf("max votes: %i\n", max_votes);
    return;
    }
 
 
    
    
