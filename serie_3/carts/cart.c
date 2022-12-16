#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cart.h"
#include "../get_json/get_json.h"

void carts_list_init(Carts *carts_list) {
	carts_list->carts = list_create();
	carts_list->total = 0;
}

void print_cart(void *cart) {
	Cart *data = (Cart *)cart;
	printf("\n###\t Cart \t###\n\n");
	printf("user id: %d\n", data->user_id);
	printf("##Products\n\n");
	printf("total products: %ld \n", data->n_products);
	
	for(int i = 0; i < data->n_products; i++) {
		printf("\n\t#Product\n");
		printf("\tId: %d\n", data->products[i].id);
		printf("\tQuantity: %ld\n", data->products[i].quantity);
	}
}

void print_carts(Carts *carts_list) {
	printf("Número de carrinhos = %d\n", carts_list->total);
	if(carts_list->total > 0)
		list_foreach(carts_list->carts, print_cart);
	else
		printf("\n\t ### No carts ### \t\n");
}

int cmp_id(void *item, void *id) {
	void *data = ((Node *)item)->data;
	return ((Cart *)data)->user_id == *((int *) id);
}

void cart_insert(Carts *carts_list, int user_id, size_t n_products, struct { int id; size_t quantity; } products[]) {
	
	//verificar se a lista de produtos a ser inserida tem produtos com ids diferentes
	Cart *cart = malloc(sizeof *cart);
	cart->user_id = user_id;
	cart->n_products = n_products;
	
	for(int i = 0; i < n_products; i++) {
		//cart->products[i].id = products[i].id;
		//cart->products[i].quantity = products[i].quantity;
		printf("{id: %d, quantity: %ld}\n", products[i].id, products[i].quantity);
	}
	memcpy(cart->products, products, sizeof(products));
	
	list_insert_front(carts_list->carts, cart);
	carts_list->total += 1;
}

void cart_delete(void *cart) {
	free(cart);
}

void cart_remove(Carts *carts_list, int user_id) {
	Node *cart = list_find(carts_list->carts, cmp_id, &user_id);
	if(cart != NULL) {
		list_remove(cart);
		cart_delete(cart->data);
		carts_list->total -= 1;
	} 
	else 
		fprintf(stderr, "Cart with user_id [%d] does not exist\n", user_id);
}

void carts_list_delete(Carts *carts_list) {
	list_destroy(carts_list->carts, cart_delete);
	free(carts_list);
}

Carts *carts_get() {
	Carts *carts_list = malloc(sizeof *carts_list);
	carts_list_init(carts_list);
	json_t *res = http_get_json_data("https://dummyjson.com/carts");
	json_t *json_array = json_object_get(res, "carts");
	
	for(int j = 0; j < json_array_size(json_array); j++) {
		json_t *obj = json_array_get(json_array, j);
		json_t *user_id_value = json_object_get(obj, "userId");
		json_t *products_array_value = json_object_get(obj, "products");
		json_t *total_products_value = json_object_get(obj, "totalProducts");
		
		int user_id = json_integer_value(user_id_value);
		int total_products = json_integer_value(total_products_value);
		
		struct { int id; size_t quantity; } products[total_products];
		
		for (int i = 0; i < total_products; i++) {
			json_t *obj_prod = json_array_get(products_array_value, i);
			json_t *product_id_value = json_object_get(obj_prod, "id");
			json_t *quantity_value = json_object_get(obj_prod, "quantity");
			
			int id = json_integer_value(product_id_value);
			size_t quantity = json_integer_value(quantity_value);
			
			//printf("[id:%d -> quantity:%ld]", id, quantity);
			
			products[i].id = id;
			products[i].quantity = quantity;
		}
		
		//maybe check if property exists else error creating product
		cart_insert(carts_list, user_id, total_products, products);
	}
	json_decref(res); //free memory used by get_json
	return carts_list;
}


int main() {
	Carts *carts_list = carts_get();
	print_carts(carts_list);
	carts_list_delete(carts_list);
}
