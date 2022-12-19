#include "../list/list.h"

typedef struct {
	int user_id;
	size_t n_products;
	struct {
		int id;
		size_t quantity;
	} products[];
} Cart;

typedef struct {
	Node *carts;
	int total;
} Carts;

void carts_list_init(Carts *carts_list);

void print_cart(void *cart);

void print_carts(Carts *carts_list);

int cmp_id_cart(void *item, void *id);

void cart_insert(Carts *carts_list, int user_id, size_t n_products, void *prods);

void cart_delete(void *cart);

void cart_remove(Carts *carts_list, int user_id);

void carts_list_delete(Carts *carts_list);

Carts *carts_get();
