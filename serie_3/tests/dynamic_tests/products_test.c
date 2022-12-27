#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../products/product.h"

static FILE *fp;

void write_in_file(void *d) {
	Product *data = (Product *)d;
	fprintf(fp, "%d, %.2f, %s, %s\n", data->id, data->price, data->description, data->category);
}

int main() {
	
	fp = fopen("../csv_files/products.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file\n");
		exit(1);
	}
	
	Products *products_list;
	
	void* handle = dlopen("libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	Products* (*prod_get)(void) = dlsym(handle, "products_get");
	if (prod_get == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	products_list = prod_get();
	
	void (*print_prods)(Products *products_list) = dlsym(handle, "print_products");
	if (print_prods == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_prods(products_list);
	
	fprintf(fp, "id, price, description, category\n");
	
	void (*li_for)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (li_for == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	li_for(products_list->products, write_in_file);
	
	void (*prods_del)(Products *products_list) = dlsym(handle, "products_list_delete");
	if (prods_del == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	prods_del(products_list);
	dlclose(handle);
	return 0;
}
