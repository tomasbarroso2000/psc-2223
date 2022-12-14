#include "../list/list.h"

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

int cmp_id(void *item, void *id);

static void user_insert(Users *users_list, int id, const char *name);

static void user_delete(void *user);

static void user_remove(Users *users_list, int id);

static void users_list_delete(Users *users_list);

Users *users_get();

