#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<math.h>



int main(void)
{

    string s = get_string("Text: ");
    float word_count = 0;
    float sentence = 0;
    float letter = 0;

    for (int i = 0; i<strlen(s); i++)

    {
        if((s[i] == ' ' && s[i+1] != ' ') || (i == 0 && s[i+1] != ' '))
        {
        word_count++;

        }

        if(s[i] == '.' || s[i] =='!' || s[i] == '?')
            {
            sentence++;
            }

        if(isalpha(s[i]))
            {
                letter++;
            }


    }

float L = (100/word_count)*letter;
float S = (100/word_count)*sentence;


int index = round(0.0588 * L - 0.296 * S - 15.8);



    if (index < 1)
        { 
        printf("Before Grade 1\n");
        
        }
        
    else if (index >= 16)
        { 
        printf("Grade 16+\n");
        
        }
        
        else
        printf("Grade %i\n", index);


}

