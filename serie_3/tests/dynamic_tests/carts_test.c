#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../carts/cart.h"

static FILE *fp;

void write_in_file(void *d) {
	Cart *data = (Cart *)d;
	fprintf(fp, "%d, %ld\n", data->user_id, data->n_products);
	for(int i = 0; i < data->n_products; i++) {
		fprintf(fp, "\t id, quantity\n");
		fprintf(fp, "\t%d, %ld\n", data->products[i].id, data->products[i].quantity);
	}
}

int main() {
	
	Carts *carts_list;
	
	void* handle = dlopen("libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	Carts* (*carts_get_lib)(void) = dlsym(handle, "carts_get");
	if (carts_get_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	carts_list = carts_get_lib();
	
	void (*print_carts_lib)(Carts *carts_list) = dlsym(handle, "print_carts");
	if (print_carts_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_carts_lib(carts_list);
	
	fp = fopen("../csv_files/carts.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file carts.csv\n");
		exit(1);
	}
	
	fprintf(fp, "user id, number of products\n");
	
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (list_foreach_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	
	list_foreach_lib(carts_list->carts, write_in_file);
	
	void (*carts_list_delete_lib)(Carts *carts_list) = dlsym(handle, "carts_list_delete");
	if (carts_list_delete_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	carts_list_delete_lib(carts_list);
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close plugin: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}
