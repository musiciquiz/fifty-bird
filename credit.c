# include <cs50.h>
# include <stdio.h>
# include <math.h>

int main(void)
{
    // prompt input
    long card = get_long("What is your credit card number:\n");
    // calculate checksum 
    // initiate global variables
    long counter_even = 10;
    long counter_odd = 1;
    int sum_even= 0;
    int sum_odd = 0;
    //finding sum even numbers
    for (long i = 100; i < 56000000000000000; i *= 100)
    {
        int x = (card % i) / counter_even;
        
        counter_even *= 100;
        x *= 2;
        //what if double digit number?
        if (x > 9)
        {
            x = ( x % 10 ) + 1;
        }
        
        sum_even += x;
    }
    
    //finding sum odd numbers
    for (long i = 10; i < 56000000000000000; i *= 100)
    {
        int x = (card % i) / counter_odd;
        counter_odd *= 100; 
        sum_odd += x;
    }
    int checksum = sum_even + sum_odd;
    
    // check for card length and starting digits
    // VISA - 13 digit and starts with 4
    if (card >= 4000000000000 && card < 5000000000000 && checksum % 10 == 0)
    {
        printf("VISA\n");
    }
    // VISA - 16 digit and start with 4
    else if (card >= 4000000000000000 && card < 5000000000000000 && checksum % 10 == 0)
    {
        printf("VISA\n");
    }
    // MASTERCARD 16 digit start 51,52,53,54,55
    else if (card >= 5100000000000000 && card < 5600000000000000 && checksum % 10 == 0)
    {
        printf("MASTERCARD\n");
    }
    // AMEX 15 digit starts 34 or 37
    else if (card >= 340000000000000 && card < 350000000000000 && checksum % 10  == 0)
    {
        printf("AMEX\n");
    }
    else if (card >= 370000000000000 && card < 380000000000000 && checksum % 10 == 0)
    {
        printf("AMEX\n");
    }
        
    else
    {
        printf("INVALID\n");
    }
        
}




// print AMEX etc..
