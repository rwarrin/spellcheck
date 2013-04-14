#Spellcheck

Spellcheck is a command line spellchecker! The program loads a specified dictionary into memory using a trie. Only words containing alphabetic characters and apostrophes are checked, numbers and words containing numbers are skipped along with punctuation.

##Build it

To build spellcheck run `make` from the root of the project directory.

##Usage

```
./spellcheck dictionary input_file
```

`Dictionary` is a file containing a list of words used to build the dictionary in the program.

`input_file` is the file to be spell checked.
