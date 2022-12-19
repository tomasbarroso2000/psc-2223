#include <stdio.h>
#include <stdlib.h>
#include "command.h"

void command_print() {
	print_commands(commands_list)
}

int main() {
	Commands *commands_list = malloc(sizeof *commands_list);
	commands_list_init(commands_list);
	command_insert(commands_list, 'h', "list available commands", );
	(Command *)(commands_list->commands->next->data)->command();
}
