#include <stdio.h>
#include "../../users/user.h"

void command_function() {
	Users *users_list = users_get();
	int id;
	printf("\nFind user by Id\n");
	printf("\tId> ");
	scanf("%d", &id);
	
	if(id == 0) {
		fprintf(stderr, "invalid id\n");
		return;
	}
	Node *user = list_find(users_list->users, cmp_id_user, &id);
	if(user == NULL) {
		fprintf(stderr, "User with id [%d] does not exist\n", id);
		return;
	}
	printf("\n\n######\tUser\t######\n");
	print_user(user->data);
	
	users_list_delete(users_list);
}	

char command_letter = 'f';

char *command_description = "\tFind user name by id";
