#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "../utils.h"

void data_list_init(Datalist *data_list){
	data_list->datalist = list_create();
	data_list->total = 0;
}

void print_data(void *data) {
	Data *dt = (Data *)data;
	printf("\n######\t Data \t######\n\n");

	User *user = dt->user;
	printf("user_id: %d\n", user->id);
	printf("user_name: %s\n", user->name);
	
	printf("##Products\n\n");
	printf("total products: %ld \n", dt->n_products);
	
	for(int i = 0; i < dt->n_products; i++) {
		printf("\n\t#Product\n");
		printf("\tId: %d\n", dt->products[i].product->id);
		printf("\tPrice: %.2f€\n", dt->products[i].product->price);
		printf("\tQuantity: %ld\n", dt->products[i].quantity);
	}
}

void print_data_users(void *data) {
	Data *dt = (Data *)data;
	
	/*printf("\n######\t Users \t######\n\n");
	User *user = dt->user;
	printf("user_id: %d\n", user->id);
	printf("user_name: %s\n", user->name);*/
	print_user_lib(dt->user);
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
	return ((Data *)data)->user == ((User *) user);
}

void data_insert(Datalist *data_list, User *user, size_t n_products, void *prods){
	Data *data = malloc(sizeof(*data) + DATA_SIZE(n_products));
	data->user = user;
	//memcpy(data->user, user, sizeof(user));
	//printf("user_id: %d\n", data->user->id);	
	data->n_products = n_products;	
	
	struct { Product *product; size_t quantity; } products[n_products];
	memmove(products, prods, DATA_SIZE(n_products));
	
	//printf("total:%ld\n", n_products);
	for(int i = 0; i < n_products; i++) {
		//printf("id: %d\n", (products[i].product)->id);
		//memcpy(&(data->products[i].product), products[i].product, sizeof(products[i].product));
		data->products[i].product = products[i].product;
		//printf("prod_id: %d\n", (data->products[i].product)->id);
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
