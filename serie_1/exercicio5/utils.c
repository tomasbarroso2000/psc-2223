#include "find_and_substitute.h"

size_t n_words = 0;

size_t get_n_words() {
	return n_words;
}

char* str_lower(char str[]) {
	strcpy(temp, str);
	for(int j = 0; j < strlen(temp); j++) {
		char t = str[j];
		temp[j] = tolower(t);
	}
	return temp;
}

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

char* get_words(bool is_upper) {
	strcpy(str_temp, " ");
	for (size_t i = 0; i < n_words; i++) {
		if(is_upper == true)
			strcat(str_temp, words[i].word);
		else
			strcat(str_temp, str_lower(words[i].word));
		if(i != n_words - 1) strcat(str_temp, " ");
	}
	return str_temp;
}

void print_words() {
	for (size_t i = 0; i < n_words; i++) {
		printf("%s", words[i].word);
		if(i != n_words - 1) printf(" ");
	}
}

