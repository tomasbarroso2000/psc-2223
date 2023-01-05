#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"
#include <dlfcn.h>
#include <errno.h>

static Commands *commands_list;


void commands_list_init() {
	commands_list = malloc(sizeof *commands_list);
	commands_list->commands = list_create();
	commands_list->total = 0;
}

void print_command(void *command) {
	Command *data = (Command *)command;
	//printf("\n###\t Command \t###\n\n");
	printf("Letter: %c\n", data->letter);
	printf("Description: %s\n\n", data->description);
}

void print_commands() {
	printf("\n\t COMMANDS \t\n\n");
	printf("Total number of commands = %d\n\n", commands_list->total);
	if(commands_list->total > 0)
		list_foreach(commands_list->commands, print_command);
	else
		printf("\n\t No available commands \t\n");
}

int cmp_letter_command(void *item, void *letter) {
	void *data = ((Node *)item)->data;
	return ((Command *)data)->letter == *((char *) letter);
}

void command_insert(char letter, char *description, void *command) {
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

void product_remove(char letter) {
	Node *command = list_find(commands_list->commands, cmp_letter_command, &letter);
	if(command != NULL) {
		list_remove(command);
		command_delete(command->data);
		commands_list->total -= 1;
	} 
	else 
		fprintf(stderr, "Command with letter [%c] does not exist\n", letter);
}

void products_list_delete() {
	list_destroy(commands_list->commands, command_delete);
	free(commands_list);
}

// Start...
//static Command *commands = NULL;

void command_execute(char letter, char *param) {
	Node *command_node = list_find(commands_list->commands, cmp_letter_command, &letter);
	
	if (command_node == NULL) return;
	
	Command *cmd = (Command *) (command_node->data);
	
	void (*func) (void *) =  *cmd->func;
	
	func(param);
	
	return;
		
}

//static void *handle;

void command_new(char *lib) {
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
	command_insert(*letter, *description, *func);
}


/*
void leave_program(char *unused) {
	void *next;
	for (User *p = queue.next; p != &queue; p = next) {
		next = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p->name);
		free(p);
	}
	for (Command *p = commands; p != NULL; p = next) {
		next = p->next;
		free(p->desc);
		free(p);
	}
	if (handle != NULL)
		dlclose(handle);
	exit(0);
}*/



