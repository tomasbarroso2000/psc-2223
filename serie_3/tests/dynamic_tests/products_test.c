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
	
	Products *products_list;
	
	void* handle = dlopen("libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	Products* (*products_get_lib)(void) = dlsym(handle, "products_get");
	if (products_get_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	products_list = products_get_lib();
	
	void (*print_products_lib)(Products *products_list) = dlsym(handle, "print_products");
	if (print_products_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_products_lib(products_list);
	
	fp = fopen("../csv_files/products.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file products.csv\n");
		exit(1);
	}
	
	fprintf(fp, "id, price, description, category\n");
	
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (list_foreach_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	
	list_foreach_lib(products_list->products, write_in_file);
	
	void (*products_lists_delete_lib)(Products *products_list) = dlsym(handle, "products_list_delete");
	if (products_lists_delete_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	products_lists_delete_lib(products_list);
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close plugin: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	
	fclose(fp);
	return 0;
}
