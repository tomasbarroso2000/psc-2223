#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../utils.h"

int main() {
	
	Products *products_list = get_products_lib();
	print_products_lib(products_list);
	products_write_in_file_lib(products_list);
	products_delete_lib(products_list);
	
	return 0;
}
