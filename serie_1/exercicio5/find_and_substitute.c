//Compile with: gcc -g ./utils.c ../exercicio4/string_find_substitute.c  find_and_substitute.c -o find_and_substitute

#include "find_and_substitute.h"

/**
 * Function Responsible for replacing full Words by index
 **/
void replace_full_words(int i, char old_word[], char new_word[], bool is_upper) {
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
}

/**
 * Function Responsible for producing the result of the
 * desired command, in the output file ou standart output,
 * depending on the user's option
 **/
void write_output_file(char *output_file_name, bool is_word_complete, FILE *fd_output) {
	if(strcmp(output_file_name, "") == 0) {
		printf("+++\tOutput\t+++\n");
		if(is_word_complete == true) {
			print_words();
		} else {
			//printf("All words final: %s\n", all_words);
			//fputs(all_words, fd_output);
			printf("%s\n", all_words);
		}
		printf("\n");
	} else {
		fd_output = fopen(output_file_name, "w");
		if (fd_output == NULL) {
			fprintf(stderr, "fopen(%s): %s\n", output_file_name, strerror(errno));
			exit(1);
		}
		if(is_word_complete == true) {
			for(size_t i = 0; i < get_n_words(); i++) {
				fputs(words[i].word, fd_output);
				fputs(" ", fd_output);
			}
		} else {
			fputs(all_words, fd_output);
		}
		fclose(fd_output);
	}
}

/**
 * Function Responsible for reading all the words present in a specific file
 * and insert all the words in the Word list in file find_and_subtitute.h
 **/
void read_file(FILE *fd_input, char *input_file_name) {
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
}

/**
 * Function Responsible for processing the string with the words
 * that will be afected, depending the user's options it will receive
 * that string in the standart input or an input file
 **/
void read_input_file(char *input_file_name, FILE *fd_input) {
	if (strcmp(input_file_name, "") != 0) {
		read_file(fd_input, input_file_name);
	} else {
		printf("Write sentence, end with enter:\n");
		char str[WORD_MAX];
		fgets(str, WORD_MAX, stdin);
		str[strcspn(str, "\n")] = 0;
		char *ptr = strtok(str, " ");
		while(ptr != NULL){
			insert_word(ptr);
			ptr = strtok(NULL, " ");
		}
	}
}

/**
 * Function responsible for process the command 
 * it aggregates all of the above auxiliary functions and receives a Command
 * with all the user's options so that the words replacement is done correctlly
 **/
void execute_command(Command cmd) {
	FILE *fd_input;
	FILE *fd_output;
	strcpy(old_word_lower, str_lower(cmd.old_word));
	
	read_input_file(cmd.input_file_name, fd_input);
	
	if(cmd.is_word_complete == false) {
		strcpy(all_words, get_words(cmd.is_upper));
		if(cmd.is_upper == false) {
			//Case insensitive
			string_find_substitute(all_words, old_word_lower, cmd.new_word);
		}
		else{
			//Case sensitive
			string_find_substitute(all_words, cmd.old_word, cmd.new_word);
		}
	} else {
		for(size_t i = 0; i < get_n_words(); i++) {
			//Replace complete words -w
			replace_full_words(i, cmd.old_word, cmd.new_word, cmd.is_upper);
		}
	}
		
	write_output_file(cmd.output_file_name, cmd.is_word_complete, fd_output);
}

int main(int argc, char *argv[]) {
	int i = 0;
	int opt, optind = 0;
	char old_word[WORD_SIZE_MAX];
	char new_word[WORD_SIZE_MAX];
	bool is_upper = false;
	bool is_word_complete = false;
	char output_file_name[FILE_SIZE_MAX] = "";
	char input_file_name[FILE_SIZE_MAX] = "";
	
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
                    fprintf(stderr, "Option -%c requires an operand\n", optopt);
                    exit(-1);
                    break;
			case '?':
                    fprintf(stderr,"Unrecognized option: -%c\n", optopt);
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
	
	Command cmd = { is_upper, is_word_complete, output_file_name, input_file_name, old_word, new_word };
	execute_command(cmd);
}
