#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "product.h"

static Products products_list;

void products_list_init() {
	Node *node = new_list();
	products_list.products = node;
	products_list.total = 0;
}

void print_product(void *product) {
	Product *data = (Product *)product;
	printf("\n###\t Product \t###\n\n");
	printf("id: %d\n", data->id);
	printf("price: %f €\n", data->price);
	printf("description: %s\n", data->description);
	printf("category: %s\n", data->category);
}

void print_products(Products products_list) {
	printf("Número de produtos = %d\n", products_list.total);
	if(products_list.total > 0)
		list_foreach(products_list.products, print_product);
	else
		printf("\n\t ### No products ### \t\n");
}

int cmp_id(void *item, void *id) {
	void *data = ((Node *)item)->data;
	return ((Product *)data)->id == *((int *) id);
}

static void product_insert(int id, float price, const char *description, const char *category) {
	
	if(list_find(products_list.products, cmp_id, &id) != NULL) {
		fprintf(stderr, "Product with id [%d] already exists\n", id);
	}

	Product *product = malloc(sizeof *product);
	product->id = id;
	product->price = price;
	product->description = malloc(strlen(description) + 1);
	memmove((void *)product->description, description, strlen(description) + 1);
	product->category = malloc(strlen(category) + 1);
	memmove((void *)product->category, category, strlen(category) + 1);
	list_insert_prev(products_list.products, product);
	products_list.total+=1;
}

static void product_delete(void *product) {
	Product *p = (Product*)product;
	free((void *)(p->description));
	free((void *)(p->category));
	free(product);
}

static void product_remove(int id) {
	Node *n = list_find(products_list.products, cmp_id, &id);
	if(n != NULL) {
		list_remove(n);
		product_delete(n->data);
		products_list.total-=1;
	} 
	else 
		fprintf(stderr, "Product with id [%d] does not exist\n", id);
}

static void products_delete(Products products_list) {
	list_destroy(products_list.products, product_delete);
	free(products_list.products);
}

int main() {
	products_list_init();
	product_insert(1, 2.0, "samsung galaxy", "smartphone");
	product_insert(2, 1200.0, "PC Gamer AZUS", "Ultimate gaming PZ");
	print_products(products_list);
	//product_remove(1);
	//product_remove(2);
	printf("\n########### Remove ############\n");
	print_products(products_list);
	products_delete(products_list);
}
