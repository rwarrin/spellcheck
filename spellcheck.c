/*******************************************************************************
 * spellcheck.c
 *
 * Rick W
 *
 * Simple spell checker. Reads a text file containing a dictionary and checks
 * the spelling of the specified file.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "checker.h"

int main(int argc, char *argv[])
{
    // check for correct argument usage
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s dictionary input_file\n", argv[0]);
        return 1;
    }

    // attempt to load the dictionary
    bool success = Dictionary_Load(argv[1]);
    if(!success)
        return 2;

    // attempt to load the file to be spell checked
    success = Checker_Load(argv[2]);
    if(!success)
        return 3;

    // check the spelling of the file
    Checker_CheckSpelling();

    // unload the dictionary from memory
    success = Dictionary_Unload();
    if(!success)
    {
        fprintf(stderr, "Failed to unload the dictionary from memory.\n");
        return 4;
    }

    return 0;
}
