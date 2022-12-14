#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "user.h"

static FILE *fp;

void write_in_file(void *d) {
	User *data = (User *)d;
	fprintf(fp, "%d, %s\n", data->id, data->name);
}

int main() {
	
	fp = fopen("../users.csv","w");
	
	if (fp == NULL) {
		fprintf(stderr, "could not create file\n");
		exit(1);
	}
	
	Users *users_list = users_get();
	print_users(users_list);
	list_foreach(users_list->users, write_in_file);
	users_list_delete(users_list);
	fclose(fp);
}
