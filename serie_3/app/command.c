#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"

void commands_list_init(Commands *commands_list) {
	commands_list->commands = list_create();
	commands_list->total = 0;
}

void print_command(void *command) {
	Command *data = (Command *)command;
	printf("\n###\t Command \t###\n\n");
	printf("Letter: %c\n", data->letter);
	printf("Description: %s\n", data->description);
}

void print_commands(Commands *commands_list) {
	printf("Número de comandos = %d\n", commands_list->total);
	if(commands_list->total > 0)
		list_foreach(commands_list->commands, print_command);
	else
		printf("\n\t ### No commands ### \t\n");
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
	new_command->command = command;
	list_insert_front(commands_list->commands, new_command);
	commands_list->total += 1;
}

void command_delete(void *command) {
	Command *c = (Command*)command;
	free((void *)(c->description));
	free(command);
}

void product_remove(Commands *commands_list, char letter) {
	Node *command = list_find(commands_list->commands, cmp_letter_command, &letter);
	if(command != NULL) {
		list_remove(command);
		command_delete(command->data);
		commands_list->total -= 1;
	} 
	else 
		fprintf(stderr, "Command with letter [%c] does not exist\n", letter);
}

void products_list_delete(Commands *commands_list) {
	list_destroy(commands_list->commands, command_delete);
	free(commands_list);
}
