#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"
#include <dlfcn.h>
#include <errno.h>



void commands_list_init(Commands *commands_list) {
	commands_list->commands = list_create();
	commands_list->total = 0;
}

void print_command(void *command) {
	Command *data = (Command *)command;

	printf("Letter: %c\n", data->letter);
	printf("Description: %s\n\n", data->description);
}

int cmp_letter_command(void *item, void *letter) {
	void *data = ((Node *)item)->data;
	return ((Command *)data)->letter == *((char *) letter);
}

void command_insert(Commands *commands_list, char letter, char *description, void *command) {
	if(list_find(commands_list->commands, cmp_letter_command, &letter) != NULL) {
		fprintf(stderr, "Command with letter [%c] already exists!\n", letter);
	}

	Command *new_command = malloc(sizeof *new_command);
	new_command->letter = letter;
	new_command->description = malloc(strlen(description) + 1);
	memmove((void *)new_command->description, description, strlen(description) + 1);
	new_command->func = command;
	list_insert_front(commands_list->commands, new_command);
	commands_list->total += 1;
}

void command_delete(void *command) {
	Command *c = (Command*)command;
	free((void *)(c->description));
	free(command);
}

void command_remove(Commands *commands_list, char letter) {
	Node *command = list_find(commands_list->commands, cmp_letter_command, &letter);
	if(command != NULL) {
		list_remove(command);
		command_delete(command->data);
		commands_list->total -= 1;
	} 
	else 
		fprintf(stderr, "Command with letter [%c] does not exist\n", letter);
}

void commands_list_delete(Commands *commands_list) {
	list_destroy(commands_list->commands, command_delete);
	free(commands_list);
}


void command_execute(Commands *commands_list, char letter, char *param) {
	Node *command_node = list_find(commands_list->commands, cmp_letter_command, &letter);
	
	if (command_node == NULL) {
		printf("Invalid command.\nPlease type 'h' to see the available commands.\n\n");
		return;
		}
		
	Command *cmd = (Command *) (command_node->data);
	
	void (*func) (void *) =  cmd->func;
	
	func(param);
	
	return;
		
}

void command_new(Commands *commands_list, char *lib) {
	void *handle = dlopen(lib, RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	
	void (*func) (void *) = dlsym(handle, "command_function");
	if (func == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	char *letter = dlsym(handle, "command_letter");
	if (letter == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	char **description = dlsym(handle, "command_description");
	if (description == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	command_insert(commands_list, *letter, *description, *func);
}



