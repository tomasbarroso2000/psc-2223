#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "app.h"
#include "utils.h"

void data_list_init(Datalist *data_list);

void print_data(void *data);

void print_datalist(Datalist *data_list);

int cmp_id_data(void *item, void *id);

void data_insert(Datalist *data_list, int user_id, size_t n_products, void *prods);

void data_delete(void *data);

void data_remove(Datalist *data_list, int user_id);

void data_list_delete(Datalist *data_list);

Datalist *data_list_get();


int main() {
	char line[100];
	commands_list_init();
	
	command_insert('h', "\t - Listar comandos existentes", print_commands);
	command_insert('c', "\t - Incorporar novo comando", command_new);

	while (1) {
		putchar('>');
		fgets(line, sizeof line, stdin);
		char *command = strtok(line, " \n");
		char *name = strtok(NULL, " \n");
		if (command != NULL)
			command_execute(*command, name);
	}
}
