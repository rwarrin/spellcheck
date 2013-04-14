#ifndef DICTIONARY_H
#define DICTIONARY_H

/*******************************************************************************
 * dictionary.h
 *
 * Rick W
 *
 * Interface file for dictionary functions.
 * Provides functions for loading a dictionary file, checking a word, and
 * unloading the dictionary from memory.
 ******************************************************************************/

#include <stdbool.h>

// define constants
#define MAX_WORD_LENGTH 45
#define CHARACTERS 27

/**
 * Loads the specified dictionary into memory.
 * Returns true if the dictionary was successfully loaded.
 */
bool Dictionary_Load(char *dictionary_filename);

/**
 * Removes the dictionary from memory.
 * Call this before exiting your application to free allocated memory.
 * Returns true if the dictionary was successfully unloaded.
 */
bool Dictionary_Unload();

/**
 * Spell check a single word.
 * Returns true if the word is spelled correctly, false if not.
 */
bool Dictionary_Check(char *word);

#endif
