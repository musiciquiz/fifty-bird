#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int str_len = strlen(text);
    //count total letters

    int total_letters = 0;
    int words = 1; //initialise to 1 as first character will be first word.
    int sent = 0;

    for (int i = 0, n = 1; i < str_len; i++, n++)
    {
        if (isalpha(text[i]))
        {
            total_letters += 1;
        }
        if (isblank(text[n-1]))
        {
            words += 1;
        }
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sent += 1;
        }
    }
    float L = (float)total_letters / (float)words * 100;

    float S = (float)sent / (float)words * 100;

    float index = .0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }

    //printf ("Number of letters is %i\n", total_letters);
    //printf("Number of words is %i\n", words);
    //printf("Number of sentences is %i\n", sent);
    //printf("Grade %f\n", index);
}

