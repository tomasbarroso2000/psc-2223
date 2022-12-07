#include "../list/list.h"

typedef struct {
	int id;
	float price;
	const char *description;
	const char *category;
} Product;

typedef struct {
	Node *products;
	int total;
} Products;

void products_init();

int cmp_id(void *product, void *id);

static void product_insert(int id, float price, const char *description, const char *category);

Products products_get();

