#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "../utils.h"

void data_list_init(Datalist *data_list){
	data_list->datalist = list_create();
	data_list->total = 0;
}

float cart_costs(void *prods, size_t n_products) {
	float total = 0;
	struct { Product *product; size_t quantity; } products[n_products];
	memmove(products, prods, DATA_SIZE(n_products));
	for(int i = 0; i < n_products; i++) {
		total += (products[i].product->price * products[i].quantity);
	}
	return total;
}

void print_data(void *data) {
	Data *dt = (Data *)data;

	printf("\nUSER:\n\n");
	print_user_lib(dt->user);
	
	printf("\nCART\n");
	printf("\n\tTotal products: %ld \n", dt->n_products);
	printf("\n\tTotal cost: %.2f €\n", cart_costs(dt->products, dt->n_products));
	printf("\n\tProducts\t\n");
	
	for(int i = 0; i < dt->n_products; i++) {
		print_product_lib(dt->products[i].product);
		printf("\t\t\tQuantity: %ld\n\n", dt->products[i].quantity);
	}
	
	printf("\n==========================================================================================================================================================\n");
}

void print_data_users(void *data) {
	Data *dt = (Data *)data;
	
	print_user_lib(dt->user);
	printf("\n=====================================================\n");
}

void print_datalist(Datalist *data_list){
	printf("Total number of data = %d\n", data_list->total);
	if(data_list->total > 0)
		list_foreach(data_list->datalist, print_data);	
	else
		printf("\n\tNo available data\t\n");
}

int cmp_user_data(void *item, void *user){
	void *data = ((Node *)item)->data;
	return ((Data *)data)->user == ((User *) user);
}

void data_insert(Datalist *data_list, User *user, size_t n_products, void *prods){
	Data *data = malloc(sizeof(*data) + DATA_SIZE(n_products));
	data->user = user;
	data->n_products = n_products;	
	
	struct { Product *product; size_t quantity; } products[n_products];
	memmove(products, prods, DATA_SIZE(n_products));
	

	for(int i = 0; i < n_products; i++) {
		printf("inside insert id: %d\n", (products[i].product)->id);
		data->products[i].product = products[i].product;
		
		printf("inside insert quantity: %ld\n", products[i].quantity);
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
