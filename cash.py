from cs50 import get_float

while True:
    suma = get_float("Change owed: ")
    if suma > 0:
        break
    
    
tot_change = round(suma * 100)

quarters = (tot_change - tot_change % 25)/25
dimes = ((tot_change-quarters * 25) - (tot_change - quarters * 25) % 10)/10;
nickels = ((tot_change - quarters * 25 - dimes * 10) - (tot_change - quarters * 25 - dimes * 10) % 5)/5;
pennies = tot_change - quarters * 25 - dimes * 10 - nickels * 5;

#casting to integer value
num_coins = int(quarters+dimes+nickels+pennies)

print(f"{num_coins}")
