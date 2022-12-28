#include <stdlib.h>
#include "../products/product.h"
#include "../users/user.h"
#include "../carts/cart.h"
#include "../list/list.h"

typedef struct {
	User *user;
	size_t n_products;
	struct {
		Product *product;
		size_t quantity;
	} products[];
} Data;


