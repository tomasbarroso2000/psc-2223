#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WORD_SIZE_MAX 30
#define WORD_MAX 1000

void string_reverse(char buffer[], size_t buffer_size) {
	//int len = strlen(buffer);
	int size = buffer_size;
    for (size_t i = 0; i < size/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
}

size_t get_size(char buffer[]) {
	int result = 0, i;
	for(i = 0; buffer[i] != '\0'; i++) result++;
	return result;
}

typedef struct {
	char word[WORD_SIZE_MAX];
} Word;

Word words[WORD_MAX];
size_t n_words = 0;

//char word_buffer[WORD_SIZE_MAX];

char *readword(FILE *file) {
	static char word_buffer[WORD_SIZE_MAX];

	int c = fgetc(file);
	while ((c == ' ' || c == '\t' || c == '\n') && c != EOF)
		c = fgetc(file);
	size_t i = 0;
	while (c != ' ' && c != '\t' && c != '\n' && c != EOF) {
		if (i < sizeof word_buffer - 1){
			word_buffer[i] = c;
			i++;
		}
			
		c = fgetc(file);
	}
	word_buffer[i] = 0;
	return i != 0 ? word_buffer : NULL;
}

void insert_word(char *word) {
	strcpy(words[n_words].word, word);
	n_words++;
}

void print_words() {
	for (size_t i = 0; i < n_words; i++)
		printf("%s\n", words[i].word);
}

Word* get_words() {
	return words;
}

int get_n_words() {
	return n_words;
}
