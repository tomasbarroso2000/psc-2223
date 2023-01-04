#include <stdlib.h>
#include <stdio.h>
#include "app.h"

static Products *products_list;
static Users *users_list;
static Carts *carts_list;
static Datalist *data_list;

float cart_costs(void *prods, size_t n_products) {
	float total = 0;
	struct { Product *product; size_t quantity; } products[n_products];
	memmove(products, prods, DATA_SIZE(n_products));
	for(int i = 0; i < n_products; i++) {
		total += (products[i].product->price * products[i].quantity);
	}
	return total;
}

int cmp_string(void *a, void *b) {
	return strcmp(*((char **)a), *((char **)b));
}

int cmp_costs(void *a, void *b) {
	return *((int*)a) - *((int*)b);
}


void swap(void *a, void *b) {
	Data tmp = *((Data *)a);
	*((Data *)a) = *((Data *)b);
	*((Data *)b) = tmp;
}

void create_values(void *d) {
	Cart *data = (Cart *)d;
	Node *user_node = list_find_lib(users_list->users, cmp_id_user_lib, &(data->user_id));
	if (user_node != NULL) {
		struct { Product *product; size_t quantity; } products[data->n_products];
		
		size_t total_products = 0;
		for (size_t i = 0; i < data->n_products; i++) {
			
			Node *product = list_find_lib(products_list->products, cmp_id_product_lib, &(data->products[i].id));
			if(product != NULL) {
				products[total_products].product = (Product *)(product->data);
				products[total_products].quantity = data->products[i].quantity;
				total_products++;
			}
		}
		
		if (total_products > 0) {
			User *user = (User *)(user_node->data);
			data_insert(data_list, user, total_products, products);
		}
	}
	
}

void populate() {
	data_list = malloc(sizeof *data_list);
	data_list_init(data_list);
	
	products_list = get_products_lib();
	users_list = get_users_lib();
	carts_list = get_carts_lib();
}

void sort_users(Datalist *data_list, int (*cmp)(void *, void *)) {
	any_list_foreach_lib(carts_list->carts, create_values);
	for (Node *p = data_list->datalist->next; p != data_list->datalist; p = p->next) {
		for (Node *q = p->next; q != data_list->datalist; q = q->next) {
			Data *dp = (Data *)(p->data);
			Data *dq = (Data *)(q->data);
			if (cmp(&(dq->user->name), &(dp->user->name)) < 0) {
				swap(dp, dq);
			}
		}
	}
}

void sort_carts(Datalist *data_list, int (*cmp)(void *, void *)) {
	//any_list_foreach_lib(carts_list->carts, create_values);
	
	/*for (Node *current = data_list->datalist->next; current != data_list->datalist; current = current->next) {
		for (Node *index = current->next; index != data_list->datalist; index = index->next) {
			Data *cd = (Data *)(current->data);
			Data *id = (Data *)(index->data);
			float cd_cost = cart_costs(cd->products, cd->n_products);
			float id_cost = cart_costs(id->products, id->n_products);
			if (id_cost > cd_cost) {
				printf("%d <=> %d\n", cd->user->id, id->user->id);
				swap(id, cd);
			}
		}
	} */
	
	Node *n=NULL, *temp = NULL;
    Data tempvar;//temp variable to store node data
    n = data_list->datalist->next;
    //temp = node;//temp node to hold node data and next link
    while(n != data_list->datalist){
        temp=n; 
        while (temp->next != data_list->datalist){						//travel till the second last element 
           if(cart_costs(((Data *)(temp->data))->products, ((Data *)(temp->data))->n_products)  > cart_costs(((Data *)(temp->next->data))->products, ((Data *)(temp->next->data))->n_products) )// compare the data of the nodes 
            {
              tempvar = *(Data *)(temp->data);
              *(Data *)(temp->data) = *(Data *)(temp->next->data);// swap the data
              *(Data *)(temp->next->data) = tempvar;
            }
         temp = temp->next;    // move to the next element 
        }
        n = n->next;    // move to the next node
    }
}

void print_ordered_users() {
	printf("\n\n#####\tList users (alphabetically ordered by name)\t####");
	printf("\n\n\t\t");
	sort_users(data_list, cmp_string);
	any_list_foreach_lib(data_list->datalist, print_data_users);
}

void print_ordered_prices() {
	any_list_foreach_lib(carts_list->carts, create_values);
	printf("\n\n#####\tList carts (ordered by price)\t####");
	printf("\n\n\t\t");
	sort_carts(data_list, cmp_costs);
	sort_carts(data_list, cmp_costs);
	print_datalist(data_list);
	//any_list_foreach_lib(data_list->datalist, print_data_users);
}



//-----------------------------------------------------------------------------------
float cmp_prices(float a, float b) {
	return (a) - (b);
}


void sort_dec_carts_by_price(Datalist *data_list) {
	any_list_foreach_lib(carts_list->carts, create_values);
	int a = 0;
	//while(a < 10){
		for (Node *p = data_list->datalist->next; p != data_list->datalist; p = p->next) {
			for (Node *q = p->next; q != data_list->datalist; q = q->next) {
			Data *dp = (Data *)(p->data);
			Data *dq = (Data *)(q->data);
			
			if(dp != NULL && dq != NULL){
				if (cmp_prices(cart_costs(&(dp->products), dp->n_products), cart_costs(&(dq->products), dq->n_products)) < 0) {
				//printf("Welcome, this is our command\n");
				//printf("Dp_user:%d Dp_price:%f vs Dq_user:%d Dq_price:%f\n", dp->user->id, cart_costs(&(dp->products), dp->n_products), dq->user->id, cart_costs(&(dq->products), dq->n_products));
				swap(dp, dq);		
					}
				
				}
			}
		}
		//a++;
	//}
}

void print_ordered_data_by_price() {
	//any_list_foreach_lib(carts_list->carts, create_values);
	printf("\n\n#####\tList carts (ordered by price)\t####");
	printf("\n\n\t\t");
	sort_dec_carts_by_price(data_list);
	print_datalist(data_list);
	//any_list_foreach_lib(data_list->datalist, print_data_users);
}

//-----------------------------------------------------------------------------------

int main() {
	
	populate();
	system("clear");
	
	char line[100];
	commands_list_init();
	
	command_insert('h', "\t - Listar comandos existentes", print_commands);
	command_insert('u', "\t - List users (alphabetically ordered by name)", print_ordered_users);
	//command_insert('c', "\t - List carts (ordered by price)", print_ordered_prices);
	command_insert('c', "\t - List carts (ordered by price)", print_ordered_data_by_price);
	command_insert('n', "\t - Incorporar novo comando", command_new);

	while (1) {
		putchar('>');
		fgets(line, sizeof line, stdin);
		char *command = strtok(line, " \n");
		char *name = strtok(NULL, " \n");
		if (command != NULL)
			command_execute(*command, name);
	}
}



