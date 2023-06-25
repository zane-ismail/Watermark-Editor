// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num = 0;
#include "dictionary.h"

FILE *w;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    num++;
    printf("%i: \n", num);
    printf("%i\n", toupper(word[0]) - 'A');
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictonary file
    word = (fopen(dictionary, "r"));
    if (word == NULL)
    {
        return false;
    }
    node *n;
    // Read strings from file one at a time
    while (fscanf(word, "%s", word) != EOF)
    {
        // Create a new node for each word
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;

        }
        strcpy(n->word, tmp);

        // Hash word to obtain hash function
        int h = hash(tmp);

        // Insert word into hash table at that function
        n->next = table[h];
        table[h] = n->next;
        // printf("1: %s\n", tmp);
    }
        return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    fclose(w);
    return false;
}
