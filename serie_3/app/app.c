#include <stdlib.h>
#include <stdio.h>
#include "app.h"

static Products *products_list;
static Users *users_list;
static Carts *carts_list;
static Datalist *data_list;

void create_values(void *d) {
	Cart *data = (Cart *)d;
	Node *user_node = list_find_lib(users_list->users, cmp_id_user_lib, &(data->user_id));
	if (user_node != NULL) {
		struct { Product *product; size_t quantity; } products[data->n_products];
		//size_t total_products = 0; 
		
		/*for(int j = 0;  j < data->n_products; j++) {
			Node *product = list_find_lib(products_list->products, cmp_id_product_lib, &(data->products[j].id));
			if(product != NULL) total_products++;
		}
		printf("total: %ld\n", total_products);*/
		size_t total_products = 0;
		for (size_t i = 0; i < data->n_products; i++) {
			//printf("prod_id: %d\n", data->products[i].id);
			Node *product = list_find_lib(products_list->products, cmp_id_product_lib, &(data->products[i].id));
			if(product != NULL) {
				products[total_products].product = (Product *)(product->data);
				//printf("prod_id: %d\n", (products[a].product)->id);
				products[total_products].quantity = data->products[i].quantity;
				//printf("prod_quant: %ld\n", products[a].quantity);
				total_products++;
			}
		}
		//printf("total: %d\n", a);
		//printf("##\n");
		User *user = (User *)(user_node->data);
		data_insert(data_list, user, total_products, products);
	}
	
}

void populate() {
	data_list = malloc(sizeof *data_list);
	data_list_init(data_list);
	
	products_list = get_products_lib();
	users_list = get_users_lib();
	carts_list = get_carts_lib();
	
	any_list_foreach_lib(carts_list->carts, create_values);
}

int main() {
	
	populate();
	print_datalist(data_list);
	
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

