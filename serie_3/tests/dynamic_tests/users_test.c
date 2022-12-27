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
	
	fp = fopen("../csv_files/users.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file\n");
		exit(1);
	}
	
	Users *users_list;
	
	void* handle = dlopen("libdynamic.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}
	
	Users* (*usr_get)(void) = dlsym(handle, "users_get");
	if (usr_get == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	users_list = usr_get();
	
	void (*print_users)(Users *users_list) = dlsym(handle, "print_users");
	if (print_users == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	print_users(users_list);
	
	fprintf(fp, "id, name\n");
	
	void (*li_for)(Node *list, void (*)(void *)) = dlsym(handle, "list_foreach");
	if (li_for == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	
	li_for(users_list->users, write_in_file);
	
	void (*users_del)(Users *users_list) = dlsym(handle, "users_list_delete");
	if (users_del == NULL) {
		fprintf(stderr, "dlsym: %s\n", dlerror());
		return -1;
	}
	users_del(users_list);
	dlclose(handle);
	return 0;
}
