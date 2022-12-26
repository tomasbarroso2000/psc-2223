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
	printf("\n###\t User \t###\n\n");
	printf("id: %d\n", data->id);
	printf("name: %s\n", data->name);
}


void print_users(Users *users_list) {
	printf("Número de utilizadores = %d\n", users_list->total);
	if(users_list->total > 0)
		list_foreach(users_list->users, print_user);
	else
		printf("\n\t ### No users ### \t\n");
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
		
		//maybe check if property exists else error creating product
		int id = json_integer_value(id_value);
		
		size_t size_fname = strlen(json_string_value(fname_value)) + 1;
		size_t size_mname = strlen(json_string_value(mname_value)) + 1;
		size_t size_lname = strlen(json_string_value(lname_value)) + 1;
		char *name = malloc(sizeof(*name));
		
		char *first_name = malloc(sizeof(*first_name));
		char *maiden_name = malloc(sizeof(*maiden_name));
		char *last_name = malloc(sizeof(*last_name));
		
		memmove(first_name, json_string_value(fname_value), size_fname);
		memmove(maiden_name, json_string_value(mname_value), size_mname);
		memmove(last_name, json_string_value(lname_value), size_lname);
		memmove(name, first_name, size_fname);
		strcat(name, " ");
		strcat(name, maiden_name);
		strcat(name, " ");
		strcat(name, last_name);
		user_insert(users_list, id, name);
		free(first_name);
		free(maiden_name);
		free(last_name);
		free(name);
	}
	json_decref(res); //free memory used by get_json
	return users_list;
}
