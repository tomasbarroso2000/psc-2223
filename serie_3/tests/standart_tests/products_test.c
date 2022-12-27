#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "../../products/product.h"

static FILE *fp;

void write_in_file(void *d) {
	Product *data = (Product *)d;
	fprintf(fp, "%d, %.2f, %s, %s\n", data->id, data->price, data->description, data->category);
}

int main() {
	
	fp = fopen("../csv_files/products.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file products.csv\n");
		exit(1);
	}
	
	Products *products_list = products_get();
	print_products(products_list);
	fprintf(fp, "id, price, description, category\n");
	list_foreach(products_list->products, write_in_file);
	products_list_delete(products_list);
	fclose(fp);
}
