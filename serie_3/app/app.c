#include <stdlib.h>
#include <stdio.h>
#include "app.h"

static Products *products_list;
static Users *users_list;
static Carts *carts_list;
static Datalist *data_list;

int cmp_string(void *a, void *b) {
	return strcmp(*(char **) a, *(char **) b);
}

/*void swap(Node *a, Node *b) {
	printf("swap\n");
	Node *tmp = a;
	*a = *b;
	*b = *tmp;
}*/	

void swap(void *a, void *b) {
	Data tmp = *((Data *)a);
	*((Data *)a) = *((Data *)b);
	*((Data *)b) = tmp;
}

void sort(Datalist *data_list, int (*cmp)(void *, void *)) {
	for (Node *p = data_list->datalist->next; p != data_list->datalist; p = p->next) {
		for (Node *q = data_list->datalist->next; q != data_list->datalist; q = q->next) {
			Data *dp = (Data *)(p->data);
			Data *dq = (Data *)(q->data);
			if (cmp(&(dq->user->name), &(dp->user->name)) > 0) {
				swap(dp, dq);
			}
			//printf("rotate\n");
		}
	}
}

void create_values(void *d) {
	Cart *data = (Cart *)d;
	Node *user_node = list_find_lib(users_list->users, cmp_id_user_lib, &(data->user_id));
	if (user_node != NULL) {
		struct { Product *product; size_t quantity; } products[data->n_products];
		
		size_t total_products = 0;
		for (size_t i = 0; i < data->n_products; i++) {
			
			Node *product = list_find_lib(products_list->products, cmp_id_product_lib, &(data->products[i].id));
			if(product != NULL) {
				products[total_products].product = (Product *)(product->data);
				products[total_products].quantity = data->products[i].quantity;
				total_products++;
			}
		}
		
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
	//print_datalist(data_list);
	printf("Before sort\n");
	any_list_foreach_lib(data_list->datalist, print_data_users);
	
	sort(data_list, cmp_string);
	
	printf("################\n");
	printf("After sort\n");
	any_list_foreach_lib(data_list->datalist, print_data_users);
	
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

