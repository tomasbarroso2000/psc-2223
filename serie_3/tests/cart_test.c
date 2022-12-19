#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "../carts/cart.h"

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
	
	fp = fopen("csv_files/carts.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create carts file\n");
		exit(1);
	}
	
	Carts *carts_list = carts_get();
	print_carts(carts_list);
	fprintf(fp, "user id, number of products\n");
	list_foreach(carts_list->carts, write_in_file);
	carts_list_delete(carts_list);
	fclose(fp);
}
