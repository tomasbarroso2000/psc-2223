#include "../list/list.h"

typedef struct {
	int id;
	float price;
	const char *description;
	const char *category;
} Product;

typedef struct {
	Node *products;
	int total;
} Products;

void products_list_init(Products *products_list);

void print_product(void *product);

extern void print_products(Products *products_list);

int cmp_id_product(void *item, void *id);

void product_insert(Products *products_list, int id, float price, const char *description, const char *category);

void product_delete(void *product);

void product_remove(Products *products_list, int id);

void products_list_delete(Products *products_list);

extern Products *products_get();

