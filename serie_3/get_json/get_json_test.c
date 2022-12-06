#include <stdlib.h>
#include <stdio.h>
#include "get_json.h"

int main() {
	json_t *json = http_get_json_data("https://dummyjson.com/products/1");
	print_json(json);
}
