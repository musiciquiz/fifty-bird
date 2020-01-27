#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // so I don't get confused.  command line argument is now variable called key
    string key = argv[1];
    // check for command line arguments
    if (argc != 2)
    {
        printf("Please provide key as command line argument\n");
        return 1;
    }
    // check for correct length
    if (strlen(key) != 26)
    {
        printf("Key must be 26 characters\n");
        return 1;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        // check for alpha characters
        if (isalpha(key[i]) == 0)
        {
            printf("Key must be 26 alpha characters\n");
            return 1;
        }
        //convert to upper case so for consistency
        if  (islower(key[i]))
        {
            key[i] = toupper(key[i]);
        }
    }
    // now check for unique
    for (int i = 0; i < strlen(key) - 1; i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {//compare letters after

            if (key[i] == key[j])
            {
                printf("Key must be 26 unique alpha characters\n");
            return 1;
            }
        }
    }
    // get input from user
    string input = get_string("plaintext:  ");
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // lets do ciphering
    for (int i = 0; i < strlen(input); i++)
    {
        // for upper case
        if(isupper(input[i]))
        {
            // find out what letter it is then substitute
            int letter;
            for (int j = 0; j < strlen(alpha); j++)
            {
                if(input[i] == alpha[j])
                {
                    letter = j;
                }
            }
            input[i] = key[letter];
        }
        // for lower case
        else if(islower(input[i]))
        {
            //make upper case
            input[i] = toupper(input[i]);
            int letter;
            for (int k = 0; k < strlen(alpha); k++)
            {
                if(input[i] == alpha[k])
                {
                    letter = k;
                }
            }
            input[i] = tolower(key[letter]);

        }

    }

    printf("ciphertext: %s\n ", input);
    return 0;

}