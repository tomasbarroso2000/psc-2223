typedef struct node {
	struct node *next;
	struct node *prev;
	void *data;
} Node;

void list_insert_prev(Node *list, void *data);

void list_remove(Node *node);

void list_foreach(Node *list, void (*)(void *));

void list_destroy(Node *list, void (*destroy_data)(void *));

Node *list_find(Node *list, int (*cmp)(void *, void *), void *context);
