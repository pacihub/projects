#include <stdio.h>
#include <cs50.h>
#include<math.h>

int main (void)

{
    float suma;
    
    do{
    suma = get_float("Change owed:");
    } while (suma <= 0);
    
    {
    
    
    int tot_change = round(suma*100);
    
    
    int quarters = (tot_change - tot_change%25)/25;
    int dimes = ((tot_change-quarters*25) - (tot_change - quarters*25)%10)/10;
    int nickels = ((tot_change - quarters*25 - dimes*10)-(tot_change - quarters*25 - dimes*10)%5)/5;
    int pennies = tot_change - quarters*25 - dimes*10 - nickels*5;
    
    
    
    printf("%i",quarters+dimes+nickels+pennies);
    
    
    }
    
   
    
}