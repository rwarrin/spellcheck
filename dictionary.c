#ifndef DICTIONARY_C
#define DICTIONARY_C

/*******************************************************************************
 * dictionary.c
 *
 * Rick W
 *
 * Implementation of functions defined in dictionary.h
 * For usage information read dictionary.h
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// node structure
typedef struct node
{
    bool isWord;
    struct node *next[CHARACTERS];
} node;

// declare and initialize head node
node *head = NULL;

/**
 * Helper function: Adds a word to the dictionary trie.
 * This function is only used within this file and should not be used outside
 * of it.
 * Returns true if the word was added to the trie.
 */
bool Dictionary_Add(char *word);

/**
 * Helper function: Recursively frees a node of its child nodes and itself.
 * Use the Dictionary_Unload() function if you're attempting to free a
 * dictionary outside of this file.
 * Returns true after all children nodes and specified node have been freed.
 */
bool free_node(node *n_node);

/**
 * Reads the specified file line by line and builds a trie in memory by passing
 * each read word to the Dictionary_Add() function.
 * Returns true after reading the entire file, false upon error.
 */
bool Dictionary_Load(char *dictionary_filename)
{
    // attempt to open the dictionary file
    FILE *dictionary = fopen(dictionary_filename, "r");
    if(dictionary == NULL)
    {
        fprintf(stderr, "Could not open dictionary: %s\n", dictionary_filename);
        return false;
    }

    // create the read buffer
    char *read_buffer = malloc(sizeof(char) * MAX_WORD_LENGTH + 1);
    if(read_buffer == NULL)
    {
        fprintf(stderr, "Failed to create read buffer.\n");
        return false;
    }

    // clear buffer
    memset(read_buffer, 0x0, sizeof(char) * MAX_WORD_LENGTH + 1);

    while((fscanf(dictionary, "%s", read_buffer)) != EOF)
    {
        // add word to trie
        Dictionary_Add(read_buffer);
        
        // clear buffer
        memset(read_buffer, 0x0, sizeof(char) * MAX_WORD_LENGTH + 1);
    }

    // close the dictionary file
    fclose(dictionary);

    // free the read_buffer
    free(read_buffer);

    return true;
}

/**
 * Builds a trie of nodes using each letter of the word.
 * Returns true if the word was added.
 * This function should not be used outside of this file.
 */
bool Dictionary_Add(char *word) 
{
    // if head is null create it
    if(head == NULL)
    {
        head = malloc(sizeof(node));
        memset(head, 0x0, sizeof(node));
    }

    // create a builder node
    node * builder = head;
    if(builder == NULL)
    {
        fprintf(stderr, "Head node is NULL.\n");
        return false;
    }

    // navigate trie and build as neccessary
    for(int i = 0; word[i] != '\0'; i++)
    {
        // character index within node array
        int index = 0;

        if(word[i] == '\'')  // handle apostrophe in word
            index = CHARACTERS - 1;
        else
            index = word[i] - 'a';

        // check to see if the node at the index of the current node exists
        if(builder->next[index] == NULL)
        {
            builder->next[index] = malloc(sizeof(node));
            memset(builder->next[index], 0x0, sizeof(node));
        }

        builder = builder->next[index];
    }

    // navigated through the trie to the end of the word, mark it as a word
    builder->isWord = true;

    return true;
}

/**
 * Frees the entire trie structure from memory.
 * Returns true after the structure is freed, false if no trie is pointed to by
 * head.
 */
bool Dictionary_Unload()
{
    // check if the node to be unloaded is null
    if(head == NULL)
    {
        fprintf(stderr, "Cannot unload dictionary: head is NULL\n");
        return false;
    }

    // free the trie
    free_node(head);

    return true;
}

/**
 * Recursively frees a single node of all of its children nodes by following
 * each child node to its end and repeating that for each child node before
 * finally freeing the starting n_node.
 * Returns true after freeing n_node and its children.
 */
bool free_node(node *n_node)
{
    // iterate over each node in the node array
    for(int i = 0; i < CHARACTERS; i++)
    {
        // check to make sure that the node exists
        if(n_node->next[i] != NULL)
            free_node(n_node->next[i]);
    }

    // once all children nodes are removed, remove this node
    free(n_node);
    n_node = NULL;
    return true;
}

/**
 * Checks the spelling of the specified word against the dictionary in memory.
 * Returns true if the word is spelled correctly, false if not.
 */
bool Dictionary_Check(char *word) 
{
    // check if head is a valid node
    if(head == NULL)
    {
        fprintf(stderr, "Cannot check word. No dictionary is loaded.\n");
        return false;
    }

    // create a node to walk the trie searching for the word
    node *walker = head;

    for(int i = 0; word[i] != '\0'; i++)
    {
        // create a copy of the current letter
        char character = word[i];

        // convert character to lower case
        character |= 0x20;

        // index of the character in the next array of nodes
        int index = 0;

        // handle apostrophes
        if(character == '\'')
            index = CHARACTERS - 1;
        else
            index = character - 'a';

        // keep walking the list
        walker = walker->next[index];

        // if walker reaches a dead end
        if(walker == NULL)
            return false;
    }

    return walker->isWord;
}

#endif
