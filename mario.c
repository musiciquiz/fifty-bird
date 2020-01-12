#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int height;
    //prompt user for input and check that it is an integer between 1 and 8
    do
    {height = get_int("Please enter an integer between 1 and 8:\n");}
    while (height <= 0 || height >= 9);
    for (int i = 0; i<height; i++)
    {
        // leading spaces
        for (int s = 0;s < (height- i) -1; s++)
        {
            printf(" ");
        }
        // print LHS hash
     
        for (int h= (height-i)-1; h < height ;h++)
        {
            printf("#");
        }
        //print spaces
        printf("  ");
        // print RHS hash
        for (int h= (height-i)-1; h < height ;h++)
        {
            printf("#");
        }
       //new line
       printf("\n");
       
        
    }
        
    
}
