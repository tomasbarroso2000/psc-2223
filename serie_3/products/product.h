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

extern void products_list_init(Products *products_list);

extern void print_product(void *product);

extern void print_products(Products *products_list);

int cmp_id_product(void *item, void *id);

extern void product_insert(Products *products_list, int id, float price, const char *description, const char *category);

extern void product_delete(void *product);

extern void product_remove(Products *products_list, int id);

extern void products_list_delete(Products *products_list);

extern Products *products_get();

