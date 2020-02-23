// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// keep track of number of words in dictionary
unsigned int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
   // Converts string to its lowercase representation (this code from Marek Suscak)
    char copy[strlen(word) + 1];
    strcpy(copy, word);
    char *p = copy;
    for ( ; *p; ++p) *p = tolower(*p);
    // use hash function to get index of appropriate linked list
    unsigned int index = hash(copy);

    // create temp node to use to iterate over list and assign it to first value in list
    node *temp = table[index];
    // iterate over linked list
    while (temp != NULL)
    {


        if(strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// Hashes word to a number (using djb2 algorithm attributed to Dan Bernstein)
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file and check it opens
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        return false;
    }
    //  create char array to store word
    char dword[LENGTH + 1];
    unsigned int hash_no = 0;

    //use scanf to read each work in dictionary
    while (fscanf(dict, "%s", dword) != EOF)
    {
        // create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, dword);
        n->next = NULL;

        // use hash function
        hash_no = hash(n->word);

        // assign to correct bucket and pointer
        n->next = table[hash_no];
        table[hash_no] = n;
        // add one to counter
        counter++;
    }
    // close file
    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return counter;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
