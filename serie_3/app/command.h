#ifndef COMMAND_H
#define COMMAND_H

#include "../list/list.h"

typedef struct {
	char letter;
	char *description;
	void (*func) (void *);
} Command;

typedef struct {
	Node *commands;
	int total;
} Commands;

void commands_list_init();

void print_command(void *command);

void print_commands();

int cmp_letter_command(void *item, void *letter);

void command_insert(char letter, char *description, void *command);

void command_delete(void *command);

void command_remove(char letter);

void commands_list_delete();

void command_execute(char letter, char *param);

void command_new(char *lib);

#endif
