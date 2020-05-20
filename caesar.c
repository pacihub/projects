#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>


    int main(int argc, string argv[])
{
//we make sure the argument count is 2 with this condition
if(argc != 2)
 { printf("enter only one value");

 return 1;
 }

 // return 0: is a good thing in programming. When we return value !=0 we signal the main function that program is faulty.


  //check if every symbol from argv[1] is a number. if not => game over
  for (int i = 0; i < strlen(argv[1]); i++)
  {
      if(isdigit(argv[1][i]) == 0)
      {
          printf("Usage: ./caesar key \n");
          return 1;
      }

  }


 //converting the argv value to integer
 int k = atoi(argv[1]);



    string s = get_string("plaintext: ");

  printf("ciphertext: ");
    for (int i = 0; i <=strlen(s); i++)
    {
         if(islower(s[i]))
         { s[i]= ((s[i]-97 + k)%26) +97;

         printf("%c", s[i]);
         }

          else if(isupper(s[i]))
         { s[i]= (s[i]-65 + k)%26 +65;

         printf("%c", s[i]);
         }

         else
        printf("%c",s[i]);



    }



}
