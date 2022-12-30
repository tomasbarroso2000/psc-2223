#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "app.h"
#include "../users/user.h"

#define	CART_SIZE(n_prod)	(sizeof(struct { int id; size_t quantity; }) * n_prod)


void data_list_init(Datalist *data_list){
	data_list->datalist = list_create();
	data_list->total = 0;
}

void print_data(void *data){
	Data *dt = (Data *)data;
	printf("\n######\t Data \t######\n\n");

	User *user = (User *) dt->user;
	print_user(user);
	
	printf("##Products\n\n");
	printf("total products: %ld \n", data->n_products);
	
	for(int i = 0; i < dt->n_products; i++) {
		printf("\n\t#Product\n");
		printf("\tId: %d\n", dt->products[i].id);
		printf("\tQuantity: %ld\n", dt->products[i].quantity);
	}
}

void print_datalist(Datalist *data_list){
	printf("Number of data = %d\n", data_list->total);
	if(data_list->total > 0)
		list_foreach(data_list->datalist, print_data);
	else
		printf("\n\t ### No data ### \t\n");
}

int cmp_user_data(void *item, void *user){
	void *data = ((Node *)item)->data;
	return ((Data *)data)->user == *((User *) user);
}

void data_insert(Datalist *data_list, User *user, size_t n_products, void *prods){
	struct { int id; size_t quantity; } products[n_products];
	memmove(products, prods, CART_SIZE(n_products));
	
	Data *data = malloc(sizeof(*data) + CART_SIZE(n_products));
	data->user = user;
	data->n_products = n_products;
	
	for(int i = 0; i < n_products; i++) {
		data->products[i].product = products[i];
		data->products[i].quantity = products[i].quantity;
	}
	
	list_insert_front(data_list->datalist, data);
	data_list->total += 1;
}

void data_delete(void *data){
	free(data);
}

void data_remove(Datalist *data_list, User *user){
	Node *dt = list_find(data_list->datalist, cmp_user_data, &user);
	if(dt != NULL) {
		list_remove(dt);
		data_delete(dt->data);
		data_list->total -= 1;
	} 
	else 
		fprintf(stderr, "Data with user_id [%d] does not exist\n", user->id);
}

void data_list_delete(Datalist *data_list){
	list_destroy(data_list->datalist, data_delete);
	free(data_list);
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
