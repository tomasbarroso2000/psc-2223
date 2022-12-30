#include "../list/list.h"

#ifndef USER_H
#define USER_H


typedef struct {
	int id;
	const char *name;
} User;

typedef struct {
	Node *users;
	int total;
} Users;

void users_list_init(Users *users_list);

void print_user(void *user);

void print_users(Users *users_list);

int cmp_id_user(void *item, void *id);

void user_insert(Users *users_list, int id, const char *name);

void user_delete(void *user);

void user_remove(Users *users_list, int id);

void users_list_delete(Users *users_list);

Users *users_get();

#endif
