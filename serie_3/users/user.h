#include "../list/list.h"

typedef struct {
	int id;
	const char *name;
} User;

typedef struct {
	Node *users;
	int total;
} Users;

extern void users_list_init(Users *users_list);

extern void print_user(void *user);

extern void print_users(Users *users_list);

int cmp_id_user(void *item, void *id);

extern void user_insert(Users *users_list, int id, const char *name);

extern void user_delete(void *user);

extern void user_remove(Users *users_list, int id);

extern void users_list_delete(Users *users_list);

extern Users *users_get();

