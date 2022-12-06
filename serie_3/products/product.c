#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "product.h"

static Products *products_list = NULL;

void products_init() {
	Node products = { .next = &products, .prev = &products, .data = NULL };
	products_list = malloc(sizeof *products_list);
	products_list->products = &products;
}

int cmp_id(void *product, void *id) {
	return ((Product*)product)->id == *(int*)id;
}

static void product_insert(int id, float price, const char *description, const char *category) {
	
	Node *check_id = list_find(products_list->products, cmp_id, &id);
	
	if(check_id != NULL) {
		fprintf(stderr, "Product id already exists\n");
	}

	Product *product = malloc(sizeof *product);
	product->id = id;
	product->price = price;
	product->description = malloc(strlen(description) + 1);
	strcpy(product->description, description);
	product->category = malloc(strlen(category) + 1);
	strcpy(product->category, category);
	list_insert_prev(products_list->products, product);
}

int main() {
	if (products_list == NULL)
		products_init();
	products_init();
}
