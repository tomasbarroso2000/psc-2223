#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

#define COMMANDS ":cwi:o:"
#define WORD_SIZE_MAX 30
#define WORD_MAX 1000

typedef struct {
	char word[WORD_SIZE_MAX];
} Word;

Word words[WORD_MAX];
size_t n_words = 0;

char temp[WORD_MAX];
char str_temp[100];

char* str_lower(char str[]) {
	strcpy(temp, str);
	for(int j = 0; j < strlen(temp); j++) {
		char t = str[j];
		temp[j] = tolower(t);
	}
	return temp;
}

void string_find_substitute(char *string, char *string1, char *string2);

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

void execute_command(bool is_upper, bool is_word_complete, char *output_file_name, char *input_file_name, char *old_word, char *new_word) {
	if(is_upper == false)
		printf("is upper false\n");
	else 
		printf("is upper true\n");
		
	if(is_word_complete == false)
		printf("is word false\n");
	else 
		printf("is word true\n");
		
	printf("output filename: %s\n", output_file_name);
	printf("input filename: %s\n", input_file_name);
	printf("old word: %s\n", old_word);
	printf("new word: %s\n", new_word);
	
	FILE *fd_input;
	FILE *fd_output;
	
	if (strcmp(input_file_name, "") != 0) {
		//text is in file
		fd_input = fopen(input_file_name, "r");
		if (fd_input == NULL) {
			fprintf(stderr, "fopen(%s): %s\n", input_file_name, strerror(errno));
			exit(1);
		}
		
		int size = 0;
		char *word = readword(fd_input);
		while (word != NULL) {
			insert_word(word);
			word = readword(fd_input);
		}
		
		fclose(fd_input);
		
		printf("N words: %ld\n", n_words);
		
		//replace string and not substring
		char old_word_lower[WORD_MAX];
		strcpy(old_word_lower, str_lower(old_word));
		
		char all_words[100];
		strcpy(all_words, get_words(is_upper));
		
		for(int i = 0; i < n_words; i++) {
			//Replace complete words -w
			if(is_word_complete == true) {
				if(is_upper == true) {
					//case sensitive
					if (strcmp(words[i].word, old_word) == 0) {
						strcpy(words[i].word, new_word);
					}
				} else {
					//case insensitive
					if (strcmp(str_lower(words[i].word), old_word_lower) == 0) {
						strcpy(words[i].word, new_word);
					}
				}
			} else {
				//concat all words
				
				//Replace substring words -w
				printf("All words Before: %s + old_word_lower: %s + new word: %s\n", all_words, old_word_lower, new_word);
				string_find_substitute(all_words, old_word_lower, new_word);
			}
		}
		
		if(strcmp(output_file_name, "") == 0) {
			printf("+++\tOutput\t+++\n");
			print_words();
		} else {
			printf("write in file\n");
			fd_output = fopen(output_file_name, "w");
			if (fd_output == NULL) {
				fprintf(stderr, "fopen(%s): %s\n", output_file_name, strerror(errno));
				exit(1);
			}
			if(is_word_complete == true) {
				for(int i = 0; i < n_words; i++) {
					fputs(words[i].word, fd_output);
					fputs(" ", fd_output);
				}
			} else {
				fputs(all_words, fd_output);
			}
		
			fclose(fd_output);
		}
	}
	
	
}

int main(int argc, char *argv[]) {
	int i = 0;
	int opt, optind = 0;
	char old_word[100];
	char new_word[100];
	bool is_upper = false;
	bool is_word_complete = false;
	char output_file_name[100] = "";
	char input_file_name[100] = "";
	
	
	while((opt = getopt(argc, argv, COMMANDS)) != -1) { 
        switch(opt) { 
            case 'c': 
				is_upper = true;
				break;
            case 'w':
                is_word_complete = true;
                break;
            case 'i':
				strcpy(input_file_name, optarg);
                break;
			case 'o':
				strcpy(output_file_name, optarg);
				break;
				case ':':       
                    fprintf(stderr,
                            "Option -%c requires an operand\n", optopt);
                    exit(-1);
                    break;
           case '?':
                    fprintf(stderr,
                            "Unrecognized option: -%c\n", optopt);
                
            default:
				printf("No commands option\n");
			
        } 
    }
	for (i = optind; i < argc; i++) ;
	strcpy(old_word, argv[i-2]);
	strcpy(new_word, argv[i-1]);
	
	if(old_word == NULL || new_word == NULL) {
		printf("Invalid Arguments\n");
		exit(-1);
	}
	execute_command(is_upper, is_word_complete, output_file_name, input_file_name, old_word, new_word);
	printf("arg1: %s, arg2: %s\n", old_word, new_word);
}
