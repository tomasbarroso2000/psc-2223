#include <stdlib.h>
#include <stdio.h>
#include "app.h"

static Products *products_list;
static Users *users_list;
static Carts *carts_list;
static Datalist *data_list;
static Datalist *ordered_datalist;

float cart_costs(void *prods, size_t n_products) {
	float total = 0;
	struct { Product *product; size_t quantity; } products[n_products];
	memmove(products, prods, DATA_SIZE(n_products));
	for(int i = 0; i < n_products; i++) {
		total += (products[i].product->price * products[i].quantity);
	}
	return total;
}

int cmp_string(void *a, void *b) {
	return strcmp(*((char **)a), *((char **)b));
}

void swap(Node *p, Node *q) {
  Data *temp;
  memcpy(&temp, &(p->data), sizeof(p->data));
  memcpy(&(p->data), &(q->data), sizeof(q->data));
  memcpy(&(q->data), &temp, sizeof(temp));
}

float compare_nodes(void *p, void *q) {
	Node *a = (Node *)p, *b = (Node *)q;
  float n1_cost = cart_costs(((Data *)a->data)->products, ((Data *)a->data)->n_products);
  float n2_cost = cart_costs(((Data *)b->data)->products, ((Data *)b->data)->n_products);
  return n1_cost - n2_cost;
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
		
		if (total_products > 0) {
			User *user = (User *)(user_node->data);
			data_insert(data_list, user, total_products, products);
		}
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

void sort_users(Datalist *data_list, int (*cmp)(void *, void *)) {
	for (Node *p = data_list->datalist->next; p != data_list->datalist; p = p->next) {
		for (Node *q = p->next; q != data_list->datalist; q = q->next) {
			Data *dp = (Data *)(p->data);
			Data *dq = (Data *)(q->data);
			if (cmp(&(dq->user->name), &(dp->user->name)) < 0) {
				swap(p, q);
			}
		}
	}
}

void sort_carts(Datalist *data_list, float (*cmp)(void *, void *)) {
	for (Node *current = data_list->datalist->next; current != data_list->datalist; current = current->next) {
		for (Node *index = current->next; index != data_list->datalist; index = index->next) {
			if (cmp(current, index) < 0) {
				swap(current, index);
			}
		} 
	}
}

void print_ordered_users() {
	system("clear");
	printf("\n\n \t List of Users (alphabetically ordered by name)\t\n\n");
	//printf("\n\n\t\t");
	ordered_datalist = malloc(sizeof *ordered_datalist);
	data_list_init(ordered_datalist);
	ordered_datalist = data_list;
	sort_users(ordered_datalist, cmp_string);
	any_list_foreach_lib(ordered_datalist->datalist, print_data_users);
}

void print_ordered_prices() {
	system("clear");
	printf("\n\n#####\tList carts (ordere	d by price)\t####");
	ordered_datalist = malloc(sizeof *ordered_datalist);
	data_list_init(ordered_datalist);
	ordered_datalist = data_list;
	sort_carts(ordered_datalist, compare_nodes);
	//print_datalist(data_list);
	any_list_foreach_lib(ordered_datalist->datalist, print_data_users);
}

int main() {
	
	populate();
	system("clear");
	
	char line[100];
	commands_list_init();
	
	command_insert('h', "\t - Listar comandos existentes", print_commands);
	command_insert('u', "\t - List users (alphabetically ordered by name)", print_ordered_users);
	command_insert('c', "\t - List carts (ordered by price)", print_ordered_prices);
	command_insert('n', "\t - Incorporar novo comando", command_new);

	printf("\n\t\t Welcome to the Cart Info application!\t\t\n\n");
	printf("\tHere you can check the carts, users and products information.\n");
	printf("\tTo see the available commands put 'h' below.\n\n");
	while (1) {
		putchar('>');
		fgets(line, sizeof line, stdin);
		char *command = strtok(line, " \n");
		char *name = strtok(NULL, " \n");
		if (command != NULL)
			command_execute(*command, name);
	}
}


