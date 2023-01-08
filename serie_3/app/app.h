#ifndef APP_H
#define APP_H

#include <string.h>
#include "command.h"
#include "data.h"
#include "../utils.h"

int cmp_string(void *a, void *b);

void swap(Node *p, Node *q);

float compare_nodes(void *p, void *q);

void create_values(void *d);

void populate();

void sort_users(Datalist *data_list, int (*cmp)(void *, void *));

void sort_carts(Datalist *data_list, float (*cmp)(void *, void *));

void print_ordered_users();

void print_ordered_prices();

void leave();

void help();

#endif
