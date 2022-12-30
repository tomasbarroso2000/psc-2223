#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "utils.h"

static FILE *fp;

static void *handle;

void handle_init() {
	handle = dlopen("libdynamic.so", RTLD_LAZY);
	
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
}

void handle_close() {
	if (fp != NULL) {
		fclose(fp);
	}
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		exit(1);
	}
}

void check_dlsym(void *func) {
	if (func == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		exit(1);
	}
}

/*Get Json*/

json_t* get_json_data_lib(const char *url) {
	handle_init();
	json_t* (*http_get_json)(const char *url) = dlsym(handle, "http_get_json_data");
	check_dlsym(http_get_json);
	json_t* json = http_get_json(url);
	handle_close();
	return json;
}

void print_json_lib(json_t *json) {
	handle_init();
	void (*print_json_fun)(json_t *root) = dlsym(handle, "print_json");
	check_dlsym(print_json_fun);
	print_json_fun(json);
	json_decref(json); 
	handle_close();
}


/*Products Section*/

Products* get_products_lib() {
	Products *products;
	handle_init();
	Products* (*products_get_lib)(void) = dlsym(handle, "products_get");
	check_dlsym(products_get_lib);
	products = products_get_lib();
	handle_close();
	return products;
}

void print_products_lib(Products *products) {
	handle_init();
	void (*print)(Products *products_list) = dlsym(handle, "print_products");
	check_dlsym(print);
	print(products);
	handle_close();
}

void write_in_file_products(void *d) {
	Product *data = (Product *)d;
	fprintf(fp, "%d, %.2f €, %s, %s\n", data->id, data->price, data->description, data->category);
}

void products_write_in_file_lib(Products *products_list) {
	handle_init();
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	check_dlsym(list_foreach_lib);
	fp = fopen("../csv_files/products.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file products.csv\n");
		exit(1);
	}
	
	fprintf(fp, "id, price, description, category\n");
	list_foreach_lib(products_list->products, write_in_file_products);
	handle_close();
}

void products_delete_lib(Products *products_list) {
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	handle_init();
	void (*products_list_delete_lib)(Products *products_list) = dlsym(handle, "products_list_delete");
	check_dlsym(products_list_delete_lib);
	products_list_delete_lib(products_list);
	handle_close();
}

/*Users Section*/

Users* get_users_lib() {
	Users *users;
	handle_init();
	Users* (*users_get_lib)(void) = dlsym(handle, "users_get");
	check_dlsym(users_get_lib);
	users = users_get_lib();
	handle_close();
	return users;
}

void print_users_lib(Users *users) {
	handle_init();
	void (*print)(Users *users_list) = dlsym(handle, "print_users");
	check_dlsym(print);
	print(users);
	handle_close();
}

void write_in_file_users(void *d) {
	User *data = (User *)d;
	fprintf(fp, "%d, %s\n", data->id, data->name);
}

void users_write_in_file_lib(Users *users_list) {
	handle_init();
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	check_dlsym(list_foreach_lib);
	fp = fopen("../csv_files/users.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file users.csv\n");
		exit(1);
	}
	
	fprintf(fp, "id, name\n");
	list_foreach_lib(users_list->users, write_in_file_users);
	handle_close();
}

void users_delete_lib(Users *users_list) {
	
	handle_init();
	void (*users_list_delete_lib)(Users *users_list) = dlsym(handle, "users_list_delete");
	check_dlsym(users_list_delete_lib);
	users_list_delete_lib(users_list);
	handle_close();
}

/*Carts Section*/

Carts* get_carts_lib() {
	Carts *carts;
	handle_init();
	Carts* (*carts_get_lib)(void) = dlsym(handle, "carts_get");
	check_dlsym(carts_get_lib);
	carts = carts_get_lib();
	handle_close();
	return carts;
}

void print_carts_lib(Carts *carts) {
	handle_init();
	void (*print)(Carts *carts_list) = dlsym(handle, "print_carts");
	check_dlsym(print);
	print(carts);
	handle_close();
}

void write_in_file_carts(void *d) {
	Cart *data = (Cart *)d;
	fprintf(fp, "%d, %ld\n", data->user_id, data->n_products);
	for(int i = 0; i < data->n_products; i++) {
		fprintf(fp, "\t id, quantity\n");
		fprintf(fp, "\t%d, %ld\n", data->products[i].id, data->products[i].quantity);
	}
}

void carts_write_in_file_lib(Carts *carts_list) {
	handle_init();
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	check_dlsym(list_foreach_lib);
	fp = fopen("../csv_files/carts.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file carts.csv\n");
		exit(1);
	}
	
	fprintf(fp, "user id, number of products\n");
	list_foreach_lib(carts_list->carts, write_in_file_carts);
	handle_close();
}

void carts_delete_lib(Carts *carts_list) {
	handle_init();
	void (*carts_list_delete_lib)(Carts *carts_list) = dlsym(handle, "carts_list_delete");
	check_dlsym(carts_list_delete_lib);
	carts_list_delete_lib(carts_list);
	handle_close();
}

void any_list_foreach_lib(Node *list, void (*do_it)(void *)) {
	handle_init();
	void (*li_foreach)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	check_dlsym(li_foreach);
	li_foreach(list, do_it);
	handle_close();
}

Node *list_find_lib(Node *list, int (*cmp)(void *, void *), void *context) {
	handle_init();
	void (*li_find)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	check_dlsym(list_foreach_lib);
	li_find(list, cmp, context);
	handle_close();
}

int cmp_id_user_lib(void *item, void *id) {
	handle_init();
	int (*cp_id_user)(void *item, void *id) = dlsym(handle, "cmp_id_user");
	check_dlsym(cp_id_user);
	int result = cp_id_user(item, id);
	handle_close();
	return result;
}

int cmp_id_product_lib(void *item, void *id) {
	handle_init();
	int (*cp_id_product)(void *item, void *id) = dlsym(handle, "cmp_id_product");
	check_dlsym(cp_id_product);
	int result = cp_id_product(item, id);
	handle_close();
	return cp_id_product;
}

void print_user_lib(void *user){
	handle_init();
	void (*print_u) (void *user) = dlsym(handle, "print_user");
	check_dlsym(print_u);
	print_u(user);
	handle_close();
}

void print_product(void *product){
	handle_init();
	void (*print_p) (void *product) = dlsym(handle, "print_product");
	check_dlsym(print_p);
	print_p(product);
	handle_close();
}
