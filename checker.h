#ifndef CHECKER_H
#define CHECKER_H

/*******************************************************************************
 * checker.h
 *
 * Rick W
 *
 * Contains interface functions for reading a file to be spellchecked and
 * checking words.
 ******************************************************************************/

#include <stdbool.h>

// define constants
#define MAX_WORD_LENGTH 45
#define CHARACTERS 27

/**
 * Load the file to be spellchecked.
 * Returns true if the file was loaded.
 */
bool Checker_Load(char *filename);

/**
 * Checks the spelling of the file loaded by Checker_Load().
 * Returns true if the whole file was spell checked, false  if there was an
 * error. This function closes the file opened by Checker_Load() before
 * returning.
 */
bool Checker_CheckSpelling();

#endif
