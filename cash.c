#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    // get_float for input and check input non-negative
    float amount;
    do
    {
        amount = get_float("Please enter change amount:");
    }
    while (amount <0);
    // change float to int and round to cents
    int cents = round(amount * 100);
     // how many coins and keep track
    int coins = 0;
    int change = cents;
    //quartes
    if (change / 25 > 0)
    {
        int a = change / 25;
        change = change - (a * 25);
        coins = coins + a;
    }
    // dimes
    if (change / 10 > 0)
    {
        int b = change / 10;
        change = change - (b * 10);
        coins = coins + b;
     }
    // nickels
    if (change / 5 > 0)
    {
        int c = change / 5;
        change = change - (c * 5);
        coins = coins + c;
    }
    //pennies
    coins = coins + change;
    printf("%i\n",coins);
  
}

