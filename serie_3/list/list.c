#include <stdlib.h>
#include <stdio.h>
#include "list.h"

Node *list_create() {
	Node *sentinel = malloc(sizeof *sentinel);
	if (NULL == sentinel) {
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	sentinel->next = sentinel->prev = sentinel;
	return sentinel;
}

void list_insert_front(Node *list, void *data) {
	Node *new = malloc(sizeof *new);
	if (new == NULL) {
		fprintf(stderr, "Out of memory");
		exit(-1);
	}
	
	new->prev = list->prev;
	list->prev->next = new;
	list->prev = new;
	new->next = list;
	new->data = data;
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
	free(list);
}

Node *list_find(Node *list, int (*cmp)(void *, void *), void *context) {
	for (Node *p = list->next; p != list; p = p->next)
		if (cmp(p, context))
			return p;
	return NULL;
}
