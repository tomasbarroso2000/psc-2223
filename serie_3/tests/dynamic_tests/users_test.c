#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../users/user.h"

static FILE *fp;

void write_in_file(void *d) {
	User *data = (User *)d;
	fprintf(fp, "%d, %s\n", data->id, data->name);
}

int main() {
	
	Users *users_list;
	
	void* handle = dlopen("libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	Users* (*users_lib_get)(void) = dlsym(handle, "users_get");
	if (users_lib_get == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	users_list = users_lib_get();
	
	void (*print_users_lib)(Users *users_list) = dlsym(handle, "print_users");
	if (print_users_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_users_lib(users_list);
	
	fp = fopen("../csv_files/users.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file users.csv\n");
		exit(1);
	}
	
	fprintf(fp, "id, name\n");
	
	void (*list_foreach_lib)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (list_foreach_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	
	list_foreach_lib(users_list->users, write_in_file);
	
	void (*users_list_delete_lib)(Users *users_list) = dlsym(handle, "users_list_delete");
	if (users_list_delete_lib == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	users_list_delete_lib(users_list);
	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close handle: %s\n", dlerror());
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}
