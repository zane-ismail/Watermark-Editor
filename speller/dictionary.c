// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int num = 0;
int w_length = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 70;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
// TODO
    // Hash word to obtain hash value
    w_length = strlen(word);
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
        // Case insensitive
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash;
    // TODO: Improve this hash function
    if (w_length > 1)
    {
        hash = (toupper(word[0]) - 'A') + (toupper(word[0]) - 'A') + (w_length - 1);
    }
    else
    {
        inthash = (toupper(word[0]) - 'A') + (w_length - 1);
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
        num++;

        // Return false if node is null
        if (n == NULL)
        {
            return false;
        }

        // Copy word from file to node
        strcpy(n->word, word);

        // Count letters in word
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
    return num;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Keep moving cursor until it gets to NULL
    for (int h = 0; h < LENGTH; h++)
    {
        node *cursor = table[h];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
