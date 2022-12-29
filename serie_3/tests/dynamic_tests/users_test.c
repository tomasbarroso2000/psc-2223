#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include "../../utils.h"

static FILE *fp;

void write_in_file(void *d) {
	User *data = (User *)d;
	fprintf(fp, "%d, %s\n", data->id, data->name);
}

int main() {
	
	Users *users_list = get_users_lib();
	print_users_lib(users_list);
	users_write_in_file_lib(users_list);
	users_delete_lib(users_list);
	
	return 0;
}
