#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>


static FILE *fp;

/*void write_in_file(void *d) {
	Product *data = (Product *)d;
	fprintf(fp, "%d, %.2f, %s, %s\n", data->id, data->price, data->description, data->category);
}*/

int main() {
	void* handle = dlopen("../libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	//Products products;
	
	void* (*products_get)(void) = dlsym(handle, "products_get");
	if (products_get == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	void (*print_products)(void *products_list) = dlsym(handle, "print_products");
	if (print_products == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_products(products_get());
	
	dlclose(handle);
	return 0;
}
