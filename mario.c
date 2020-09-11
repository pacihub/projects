#include <stdio.h>
#include <cs50.h>

int main(void)

{
    int height;  //height of the pyramid

    do
    {
        height = get_int("Height:");   //promting the user for height
    }
    while (height > 8 || height < 1);

    {

        for (int i = 1; i <= height; i++)   // the for loop for height(number of rows)
        {
            for (int space = 1; space <= height - i ; space++)
            {
                printf(" ");
            }

            for (int hash = 1; hash <= i; hash++)    //inner nested for loop for printing spaces
            {
                printf("#");
            }


            printf("\n");

        }
    }


}
