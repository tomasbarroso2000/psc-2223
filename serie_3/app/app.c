#include <stdlib.h>
#include <stdio.h>
#include "app.h"

static Products *products_list;
static Users *users_list;
static Carts *carts_list;
static Datalist *data_list;

void create_value(void *d) {
	Cart *data = (Cart *)d;
	Node *user_node = list_find_lib(users_list->users, cmp_id_user_lib, &(data->user_id));
	struct { Product *product; size_t quantity; } products[data->n_products];
	for (int i = 0; i < cart->n_products; i++) {
		Node *product = list_find_lib(products_list->products, cmp_id_product_lib, &(data->products[i].id));
		memcpy(products[i].product, product, sizeof(struct { Product *product; size_t quantity; }));
		products[i].quantity = data->products[i].quantity;
	}
	User *user = (User *)(user_node->data);
	data_insert(data_list, user, data->n_products, products);
}

Datalist* populate() {
	data_list = malloc(sizeof *data_list);
	data_list_init(data_list);
	
	products_list = get_products_lib();
	users_list = get_users_lib();
	
	carts_list = get_carts_lib();
	
	any_list_foreach_lib(carts_list->carts, create_values);
}

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

