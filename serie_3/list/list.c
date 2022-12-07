#include <stdlib.h>
#include <stdio.h>
#include "list.h"

Node *new_list() {
	Node *list = malloc(sizeof *list);
	if (list == NULL) {
		fprintf(stderr, "Out of memory");
		exit(1);
	}
	list->next = list->prev = list;
	list->data = NULL;
	return list;
}

void list_insert_prev(Node *list, void *data) {
	Node *node = malloc(sizeof *node);
	if (node == NULL) {
		fprintf(stderr, "Out of memory");
		exit(1);
	}
	node->data = data;
	node->next = list;
	node->prev = list->prev;
		
	list->prev->next = node;
	list->prev = node;
}

void list_remove(Node *node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}

void list_foreach(Node *list, void (*do_it)(void *)) {
	for (Node *p = list->next; p != list; p = p->next)
		do_it(p->data);
}

void list_destroy(Node *list, void (*destroy_data)(void *)) {
	for (Node *next, *p = list->next; p != list; p = next) {
		next = p->next;
		destroy_data(p->data);
		free(p);
	}
}

Node *list_find(Node *list, int (*cmp)(void *, void *), void *context) {
	for (Node *p = list->next; p != list; p = p->next)
		if (cmp(p, context))
			return p;
	return NULL;
}
