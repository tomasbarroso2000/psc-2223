#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "product.h"

static FILE *fp;

void write_in_file(void *d) {
	Product *data = (Product *)d;
	fprintf(fp, "%d, %.2f, %s, %s\n", data->id, data->price, data->description, data->category);
}

int main() {
	
	fp = fopen("products.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file\n");
		exit(1);
	}
	
	Products *products_list = products_get();
	print_products(products_list);
	list_foreach(products_list->products, write_in_file);
	products_list_delete(products_list);
	fclose(fp);
}
