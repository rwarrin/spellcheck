# compiler to use
CC = gcc 

# compiler flags
CFLAGS = -ggdb -O0 -std=c99 -Wall -Werror

# target name
DICTIONARY = spellcheck
DICTIONARY_SOURCES =  spellcheck.c dictionary.c checker.c
DICTIONARY_OBJECTS = $(DICTIONARY_SOURCES:.c=.o)

# headers
HDRS = dictionary.h checker.h

# libraries
LIBS = 

# target
$(DICTIONARY): $(DICTIONARY_OBJECTS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(DICTIONARY_OBJECTS) $(LIBS)

# clean generated files
clean:
	rm -f core $(DICTIONARY_OBJECTS) $(DICTIONARY) *.o

