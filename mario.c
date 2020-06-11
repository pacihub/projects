#include <stdio.h>
#include <cs50.h>

int main (void)

{
    int height;

    //do while loop to promp the user for values only within 1 to 8 range. The condition in the WHILE is the stuff that we do NOT want. false condition).
   do
   {
    height = get_int("Height:");
   } while ( height >8 || height <1);

   {
     // the for loop for height(number of rows)
        for (int i = 1; i <= height; i++)
        {
            //inner for loop to type spaces. compares with formula number of rows - 1. for example on row 1 out of 4 we will have 4-1 spaces.
            for (int space = 1; space<=height -i ; space++)
            {
                 printf(" ");
            }
                //inner nested loop to type #/ compares agains the current iteration for row in the biggest for loop.
                for(int hash = 1; hash<= i; hash++)
                {
                    printf("#");
                }
                
                for(int hash = 1; hash<= i; hash++)
                {
                    printf("#");
                }
                for (int space = 1; space<=height -i ; space++)
            {
                 printf(" ");
            }


        printf("\n");

        }
   }


}
