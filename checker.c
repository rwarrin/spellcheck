#ifndef CHECKER_C
#define CHECKER_C

/*******************************************************************************
 * checker.c
 *
 * Rick W
 *
 * Contains the implementation of functions defined in checker.h.
 * See checker.h for usage instructions.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#include "checker.h"

// global file handle
FILE *g_input_file = NULL;

// prototypes for helper functions
/**
 * Closes the currently opened file if it exists.
 * Returns true if the file is closed, false if a file isn't open.
 */
bool Checker_CloseFile();

/**
 * Attempts to open the file specified by filename.
 * Stores the handle to the file in a global variable to be used by other
 * Checker_ functions.
 * Returns true if the file was successfully opened, otherwise false.
 */
bool Checker_Load(char *filename)
{
    g_input_file = fopen(filename, "r");
    if(g_input_file == NULL)
    {
        fprintf(stderr, "Failed to open file %s\n", filename);
        return false;
    }

    return true;
}

/**
 * Reads the file pointed to by g_input_file and checks the spelling.
 * Reads the file one character at a time to build a valid word. Valid words
 * contain only alphabetical characters and apostrophes. Numbers and words with
 * numbers are discarded.
 * Returns true when the entire file has been checked, false if there was an
 * error. The input file is closed before this function returns.
 */
bool Checker_CheckSpelling()
{
    // make sure there is a file to read from
    if(g_input_file == NULL)
    {
        fprintf(stderr, "Missing file to check spelling in.\n");
        return false;
    }

    // attempt to create a buffer to read words into
    char *read_buffer = malloc(sizeof(char) * MAX_WORD_LENGTH + 1);
    if(read_buffer == NULL)
    {
        fprintf(stderr, "Failed to create read buffer.\n");
        Checker_CloseFile();
        return false;
    }
    // clear read_buffer
    memset(read_buffer, 0x0, sizeof(char) * MAX_WORD_LENGTH + 1);

    // read the file for words only ignore nonwords
    int index = 0;
    for(int character = fgetc(g_input_file); character != EOF; character = fgetc(g_input_file))
    {
        // only allow alphabetical characters and apostrophes
        if(isalpha(character) || (character == '\'' && index > 0))
        {
            // append character to the word
            read_buffer[index] = character;
            index++;

            // ignore strings too long to be real words
            if(index > MAX_WORD_LENGTH)
            {
                // read the rest of the string
                while((character = fgetc(g_input_file)) != EOF && isalpha(character));
                // prepare for new word
                index = 0;
            }
        }

        // ignore words with numbers
        else if(isdigit(character))
        {
            // read the rest of the string
            while((character = fgetc(g_input_file)) != EOF && isalnum(character));

            // prepare for a new word
            index = 0;
        }

        // found a new word
        else if(index > 0)
        {
            // terminate current word
            read_buffer[index] = '\0';

            // check spelling of word
            if(Dictionary_Check(read_buffer) == false)
                printf("%s is misspelled.\n", read_buffer);

            // prepare for next word
            index = 0;
        }
    }

    // free the read_buffer
    free(read_buffer);

    // close the file
    Checker_CloseFile();
    return true;
}

/**
 * Closes the file pointed to by g_input_file if a file is opened.
 * This is a helper function and cannot be used outside of checker.c
 * Returns true after the file was closed, false otherwise.
 */
bool Checker_CloseFile()
{
    if(g_input_file == NULL)
        return false;

    fclose(g_input_file);
    return true;
}

#endif
