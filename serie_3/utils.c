#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include "../products/product.h"
#include "../users/user.h"
#include "../carts/cart.h"

static void *handle = dlopen("../tests/libdynamic.so", RTLD_LAZY);

void handle_error() {
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
}

void dl_error(void *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
}

void* print_any_lib(char *type) {
	if (strcmp(type, "print_products") == 0) {
		void (*print_products_lib)(Products *products_list) = dlsym(handle, "print_products");
		dl_error(print_products_lib);
		return print_products_lib;
	}
	
	if (strcmp(type, "print_users") == 0) {
		void (*print_users_lib)(Users *users_list) = dlsym(handle, "print_users");
		dl_error(print_users_lib);
		return print_users_lib;
	}
	
	if (strcmp(type, "print_carts") == 0) {
		void (*print_carts_lib)(Carts *carts_list) = dlsym(handle, "print_carts");
		dl_error(print_carts_lib);
		return print_carts_lib;
	}
	
}

Products* get_products_lib() {
	handle_error();
	Products* (*products_get_lib)(void) = dlsym(handle, "products_get");
	
	dl_error(products_get_lib);
	
	return products_get_lib();
}

Users* get_users_lib() {
	handle_error();
	Users* (*users_get_lib)(void) = dlsym(handle, "users_get");
	
	dl_error(users_get_lib);
	
	return users_get_lib();
}

Carts* get_carts_lib() {
	handle_error();
	Carts* (*carts_get_lib)(void) = dlsym(handle, "carts_get");
	
	dl_error(carts_get_lib);
	
	return carts_get_lib();
}
