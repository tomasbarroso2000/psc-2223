#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../utils.h"

int main() {
	json_t *json = get_json_data_lib("https://dummyjson.com/products/1");
	print_json_lib(json);
	return 0;
}
