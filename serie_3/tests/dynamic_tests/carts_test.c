#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../utils.h"

int main() {
	
	Carts *carts_list = get_carts_lib();
	print_carts_lib(carts_list);
	carts_write_in_file_lib(carts_list);
	carts_delete_lib(carts_list);
	return 0;
}
