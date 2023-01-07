#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "product.h"
#include "../get_json/get_json.h"

void products_list_init(Products *products_list) {
	products_list->products = list_create();
	products_list->total = 0;
}

void print_product(void *product) {
	Product *data = (Product *)product;
	printf("\t\t\tId: %d\n", data->id);
	printf("\t\t\tPrice: %f €\n", data->price);
	printf("\t\t\tDescription: %s\n", data->description);
	printf("\t\t\tCategory: %s\n\n", data->category);
}

void print_products(Products *products_list) {
	printf("\n\t PRODUCTS \t\n\n");
	printf("Number of products = %d\n\n", products_list->total);
	if(products_list->total > 0)
		list_foreach(products_list->products, print_product);
	else
		printf("\n\t No products where found \t\n");
}

int cmp_id_product(void *item, void *id) {
	void *data = ((Node *)item)->data;
	return ((Product *)data)->id == *((int *) id);
}

void product_insert(Products *products_list, int id, float price, const char *description, const char *category) {
	
	if(list_find(products_list->products, cmp_id_product, &id) != NULL) {
		fprintf(stderr, "Product with id [%d] already exists\n", id);
	}

	Product *product = malloc(sizeof *product);
	product->id = id;
	product->price = price;
	product->description = strdup(description);
	product->category = strdup(category);
	list_insert_front(products_list->products, product);
	products_list->total += 1;
}

void product_delete(void *product) {
	Product *p = (Product*)product;
	free((void *)(p->description));
	free((void *)(p->category));
	free(product);
}

void product_remove(Products *products_list, int id) {
	Node *product = list_find(products_list->products, cmp_id_product, &id);
	if(product != NULL) {
		list_remove(product);
		product_delete(product->data);
		products_list->total -= 1;
	} 
	else 
		fprintf(stderr, "Product with id [%d] does not exist\n", id);
}

void products_list_delete(Products *products_list) {
	list_destroy(products_list->products, product_delete);
	free(products_list);
}

Products *products_get() {
	Products *products_list = malloc(sizeof *products_list);
	products_list_init(products_list);
	json_t *res = http_get_json_data("https://dummyjson.com/products");
	json_t *json_array = json_object_get(res, "products");
	
	for(int j = 0; j < json_array_size(json_array); j++) {
		json_t *obj = json_array_get(json_array, j);
		json_t *id_value = json_object_get(obj, "id");
		json_t *desc_value = json_object_get(obj, "description");
		json_t *price_value = json_object_get(obj, "price");
		json_t *category_value = json_object_get(obj, "category");
		
		int id = json_integer_value(id_value);
		char *desc = strdup(json_string_value(desc_value));
		float price = json_integer_value(price_value);
		char *cat = strdup(json_string_value(category_value));
		
		product_insert(products_list, id, price, desc, cat);
		free(desc);
		free(cat);
	}
	json_decref(res); //free memory used by get_json
	return products_list;
}
