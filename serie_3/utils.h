#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "products/product.h"
#include "users/user.h"
#include "carts/cart.h"

Products* get_products_lib();
void print_products_lib(Products *products);
void products_write_in_file_lib(Products *products_list);
void products_delete_lib(Products *products_list);

Users* get_users_lib();
void print_users_lib(Users *users);
void users_write_in_file_lib(Users *users_list);
void users_delete_lib(Users *users_list);

Carts* get_carts_lib();

#endif
