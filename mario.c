#include <stdio.h>
#include <cs50.h>

int main (void)

{
    int height;
    
   do 
   {
      height = get_int("Height:");
   } 
   while (height > 8 || height < 1);
 
   {
     
        for (int i = 1; i <= height; i++)   // the for loop for height(number of rows)
        {
            for (int space = 1; space <= height - i ; space++)  //inner for loop for printing spaces
            {
                 printf(" ");
            }
                
                for(int hash = 1; hash<= i; hash++)
                {
                    printf("#");
                }
                
            
        printf("\n");
        
        }
   }
  
    
}    
