// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int count = 0;
int w_length = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 25875;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
// TODO
    // Get length of word
    w_length = strlen(word);
    // Hash word to obtain hash value
    int h = hash(word);
    // Access linked list at that index in the hash table
    // Set cursor to first item in linked list
    node *cursor = table[h];
    // Keep moving cursor until it gets to NULL
    while (cursor != NULL)
    {
        // Traverse linked list, looking for that word
        // Return true if word is in the dictionary
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // False otherwise
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;
    // TODO: Improve this hash function
    for (int i = 0; i < w_length; i++)
    {
        // Upper case
        if (word[i] > 64 && word[i] < 91)
        {
            hash = hash + ((word[i] - 'A') * (i + 1));
        }
        // Lower case
        else if (word[i] > 96 && word[i] < 123)
        {
            hash = hash + ((word[i] - 'a') * (i + 1));
        }
        // Other characters
        else
        {
            hash = hash + (word[i]);
        }
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictonary file
    FILE *dic = (fopen(dictionary, "r"));
    if (dic == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    node *n;
    // Read strings from file one at a time
    while (fscanf(dic, "%s", word) != EOF)
    {
        // Create a new node for each word
        n = malloc(sizeof(node));
        // Keep track of words in dictionary
        count++;
        // Return false if node is null
        if (n == NULL)
        {
            return false;
        }
        // Copy word from file to node
        strcpy(n->word, word);
        // Get length of word
        w_length = strlen(word);
        // Hash word to obtain hash function
        int h = hash(word);
        // Insert word into hash table at that function
        n->next = table[h];
        table[h] = n;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Keep moving cursor until it gets to NULL
    for (int i = 0; i < N + 1; i++)
    {
        node *cursor = table[i];
        // Free each node
        while (cursor != NULL)
        {
            // Create a temporary pointer
            node *tmp = cursor;
            // Move node pointer
            cursor = cursor->next;
            // Free temporary node
            free(tmp);
        }
    }
    return true;
}
