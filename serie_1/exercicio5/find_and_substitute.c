#include "find_and_substitute.h"

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

void write_output_file(char *output_file_name, bool is_word_complete, FILE *fd_output) {
	if(strcmp(output_file_name, "") == 0) {
		printf("+++\tOutput\t+++\n");
		print_words();
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

void read_input_file(char *input_file_name, FILE *fd_input) {
	if (strcmp(input_file_name, "") != 0) {
		read_file(fd_input, input_file_name);
	} else {
		printf("Write sentence, end with enter:\n");
		char str[100];
		fgets(str, 100, stdin);
		str[strcspn(str, "\n")] = 0;
		char *ptr = strtok(str, " ");
		while(ptr != NULL){
			insert_word(ptr);
			ptr = strtok(NULL, " ");
		}
	}
}

void execute_command(Command cmd) {
	FILE *fd_input;
	FILE *fd_output;
	strcpy(old_word_lower, str_lower(cmd.old_word));
	strcpy(all_words, get_words(cmd.is_upper));
	
	read_input_file(cmd.input_file_name, fd_input);
	
	for(size_t i = 0; i < get_n_words(); i++) {
		//Replace complete words -w
		if(cmd.is_word_complete == true) {
			replace_full_words(i, cmd.old_word, cmd.new_word, cmd.is_upper);
		} else {
			//Replace substring words -w
			if(cmd.is_upper == false)
				string_find_substitute(all_words, old_word_lower, cmd.new_word);
			else 
				string_find_substitute(all_words, cmd.old_word, cmd.new_word);
		}
	}
		
	write_output_file(cmd.output_file_name, cmd.is_word_complete, fd_output);
	
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
	
	Command cmd = { is_upper, is_word_complete, output_file_name, input_file_name, old_word, new_word };
	execute_command(cmd);
}
