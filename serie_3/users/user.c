#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "../get_json/get_json.h"

void users_list_init(Users *users_list) {
	users_list->users = list_create();
	users_list->total = 0;
}


void print_user(void *user) {
	User *data = (User *)user;
	
	printf("Id: %d\n", data->id);
	printf("Name: %s\n\n", data->name);
}


void print_users(Users *users_list) {
	printf("\n\t USERS \t\n\n");
	printf("Number of users = %d\n\n", users_list->total);
	if(users_list->total > 0)
		list_foreach(users_list->users, print_user);
	else
		printf("\n\t There's no user to be found \t\n");
}


int cmp_id_user(void *item, void *id) {
	void *data = ((Node *)item)->data;
	return ((User *)data)->id == *((int *) id);
}


void user_insert(Users *users_list, int id, const char *name) {
	
	if(list_find(users_list->users, cmp_id_user, &id) != NULL) {
		fprintf(stderr, "User with id [%d] already exists\n", id);
	}

	User *user = malloc(sizeof *user);
	user->id = id;
	user->name = strdup(name);
	list_insert_front(users_list->users, user);
	users_list->total += 1;
}


void user_delete(void *user) {
	User *u = (User*)user;
	free((void *)(u->name));
	free(user);
}


void user_remove(Users *users_list, int id) {
	Node *user = list_find(users_list->users, cmp_id_user, &id);
	if(user != NULL) {
		list_remove(user);
		user_delete(user->data);
		users_list->total -= 1;
	} 
	else 
		fprintf(stderr, "User with id [%d] does not exist\n", id);
}

void users_list_delete(Users *users_list) {
	list_destroy(users_list->users, user_delete);
	free(users_list);
}

Users *users_get() {
	Users *users_list = malloc(sizeof *users_list);
	users_list_init(users_list);
	json_t *res = http_get_json_data("https://dummyjson.com/users");
	json_t *json_array = json_object_get(res, "users");
	
	for(int j = 0; j < json_array_size(json_array); j++) {
		json_t *obj = json_array_get(json_array, j);
		json_t *id_value = json_object_get(obj, "id");
		
		json_t *fname_value = json_object_get(obj, "firstName");
		json_t *mname_value = json_object_get(obj, "maidenName");
		json_t *lname_value = json_object_get(obj, "lastName");
		
		int id = json_integer_value(id_value);
		
		char *first_name = strdup(json_string_value(fname_value));
		char *middle_name = strdup(json_string_value(mname_value));
		char *last_name = strdup(json_string_value(lname_value));
		char name[strlen(first_name) + strlen(middle_name) + strlen(last_name) + 3];
		
		sprintf(name,"%s %s %s", first_name, middle_name, last_name);
		
		user_insert(users_list, id, name);
		free(first_name);
		free(middle_name);
		free(last_name);
	}
	json_decref(res); //free memory used by get_json
	return users_list;
}
