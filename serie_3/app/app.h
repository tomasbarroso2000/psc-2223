#include <stdlib.h>
#include "../products/product.h"
#include "../users/user.h"
#include "../carts/cart.h"
#include "../list/list.h"

typedef struct {
	User *user;
	size_t n_products;
	struct {
		Product *product;
		size_t quantity;
	} products[];
} Data;


typedef struct {
	Node *datalist;
	int total;
} Datalist;

void data_list_init(Datalist *data_list);

void print_data(void *data);

void print_datalist(Datalist *data_list);

int cmp_id_data(void *item, void *id);

void data_insert(Datalist *data_list, int user_id, size_t n_products, void *prods);

void data_delete(void *data);

void data_remove(Datalist *data_list, int user_id);

void data_list_delete(Datalist *data_list);

Datalist *data_list_get();
