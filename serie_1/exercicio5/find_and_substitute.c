#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define COMMANDS ":cwi:o:"

char *readword(FILE *file);
void insert_word(char *word);
void print_words();
int get_n_words();
Word* get_words();

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
		
		//print_words();
		Word[] words = get_words();
		printf("N words: %d", get_n_words());
		
		for(int i = 0; i < get_n_words(); i++) {
			printf("W[%d] = %s\n", i, *words[i]);
		}
		
	
	}
	
	fclose(fd_input);
	
	
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
