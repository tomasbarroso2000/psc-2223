#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "products/product.h"
#include "users/user.h"
#include "carts/cart.h"
#include "get_json/get_json.h"

json_t* get_json_data_lib(const char *url);
void print_json_lib(json_t *json);

Products* get_products_lib();
void print_products_lib(Products *products);
void products_write_in_file_lib(Products *products_list);
void products_delete_lib(Products *products_list);

Users* get_users_lib();
void print_users_lib(Users *users);
void users_write_in_file_lib(Users *users_list);
void users_delete_lib(Users *users_list);

Carts* get_carts_lib();
void print_carts_lib(Carts *carts);
void carts_write_in_file_lib(Carts *carts_list);
void carts_delete_lib(Carts *carts_list);

void any_list_foreach_lib(Node *list, void (*do_it)(void *));
Node *list_find_lib(Node *list, int (*cmp)(void *, void *), void *context);
int cmp_id_user_lib(void *item, void *id);
int cmp_id_product_lib(void *item, void *id);

#endif
