#include "../list/list.h"

typedef struct {
	char letter;
	char *description;
	void *command;
} Command;

typedef struct {
	Node *commands;
	int total;
} Commands;

void commands_list_init(Commands *commands_list);

void print_command(void *command);

void print_commands(Commands *commands_list);

int cmp_letter_command(void *item, void *letter);

void command_insert(Commands *commands_list, char letter, char *description, void *command);

void command_delete(void *command);

void command_remove(Commands *commands_list, char letter);

void commands_list_delete(Commands *commands_list);

