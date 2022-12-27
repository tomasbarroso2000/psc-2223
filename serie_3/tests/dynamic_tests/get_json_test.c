#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../get_json/get_json.h"

int main() {
	
	void* handle = dlopen("libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	json_t* (*http_get_json_data_lib)(const char *url) = dlsym(handle, "http_get_json_data");
	if (http_get_json_data_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	json_t *json = http_get_json_data_lib("https://dummyjson.com/products/1");
	
	void (*print_json_lib)(json_t *root) = dlsym(handle, "print_json");
	if (print_json_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_json(json);
	json_decref(json); 
	
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close plugin: %s\n", dlerror());
		return -1;
	}
}
