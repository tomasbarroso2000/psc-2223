#ifndef DATA_H
#define DATA_H

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

int cmp_user_data(void *item, void *user);

void data_insert(Datalist *data_list, User *user, size_t n_products, void *prods);

void data_delete(void *data);

void data_remove(Datalist *data_list, User *user);

void data_list_delete(Datalist *data_list);

void print_data_users(void *data);

#endif
