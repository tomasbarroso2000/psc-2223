#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "utils.h"

static FILE *fp;

/*Products Section*/

Products* get_products_lib() {
	
	Products *products;
	
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
	Products* (*products_get_lib)(void) = dlsym(handle, "products_get");
	
	if (products_get_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		exit(1);
	}
	
	products = products_get_lib();
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
	
	return products;
}

void print_products_lib(Products *products) {
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
	void (*print)(Products *products_list) = dlsym(handle, "print_products");
	
	if (print == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		exit(1);
	}
	
	print(products);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
}

void write_in_file_products(void *d) {
	Product *data = (Product *)d;
	fprintf(fp, "%d, %.2f, %s, %s\n", data->id, data->price, data->description, data->category);
}

void products_write_in_file_lib(Products *products_list) {
	
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (list_foreach_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	fp = fopen("../csv_files/products.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file products.csv\n");
		exit(1);
	}
	
	fprintf(fp, "id, price, description, category\n");
	
	list_foreach_lib(products_list->products, write_in_file_products);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	fclose(fp);
}

void products_delete_lib(Products *products_list) {
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	void (*products_list_delete_lib)(Products *products_list) = dlsym(handle, "products_list_delete");
	
	if (products_list_delete_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	products_list_delete_lib(products_list);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
}

/*Users Section*/

Users* get_users_lib() {
	Users *users;
	
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
	Users* (*users_get_lib)(void) = dlsym(handle, "users_get");
	
	if (users_get_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		exit(1);
	}
	
	users = users_get_lib();
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
	
	return users;
}

void print_users_lib(Users *users) {
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
	void (*print)(Users *users_list) = dlsym(handle, "print_users");
	
	if (print == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		exit(1);
	}
	
	print(users);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
}

void write_in_file_users(void *d) {
	User *data = (User *)d;
	fprintf(fp, "%d, %s\n", data->id, data->name);
}

void users_write_in_file_lib(Users *users_list) {
	
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (list_foreach_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	fp = fopen("../csv_files/users.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file products.csv\n");
		exit(1);
	}
	
	fprintf(fp, "id, name\n");
	
	list_foreach_lib(users_list->users, write_in_file_users);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	fclose(fp);
}

void users_delete_lib(Users *users_list) {
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	void (*users_list_delete_lib)(Users *users_list) = dlsym(handle, "users_list_delete");
	
	if (users_list_delete_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		exit(1);
	}
	
	users_list_delete_lib(users_list);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
}

Carts* get_carts_lib() {
	void *handle = dlopen("tests/dynamic_tests/libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(-1);
	}
	
	Carts* (*carts_get_lib)(void) = dlsym(handle, "carts_get");
	
	if (carts_get_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		exit(-1);
	}
	
	return carts_get_lib();
}
