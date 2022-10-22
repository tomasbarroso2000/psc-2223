#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

#define COMMANDS ":cwi:o:"
#define WORD_SIZE_MAX 30
#define FILE_SIZE_MAX 50
#define WORD_MAX 1000

/**
 * Struct that represents all of the required information
 * to run any type of command
 **/ 
typedef struct {
	bool is_upper; 
	bool is_word_complete;
	char *output_file_name;
	char *input_file_name;
	char *old_word;
	char *new_word;
} Command;

/**
 * Struct that represents a word
 **/
typedef struct {
	char word[WORD_SIZE_MAX];
} Word;

/**
 * Array of words
 **/
Word words[WORD_MAX];

char temp[WORD_MAX];
char str_temp[WORD_MAX];
char old_word_lower[WORD_MAX];
char all_words[WORD_MAX];

char* str_lower(char str[]);
void string_find_substitute(char *string, char *string1, char *string2);
char *readword(FILE *file);
void insert_word(char *word);
char* get_words(bool is_upper);
void print_words();
size_t get_n_words();
