
CFLAGS = -g -Wall

all: get_json_test products_test users_test carts_test
	
get_json_test: 
	gcc $(CFLAGS) get_json_test.c ../../get_json/get_json.c -lcurl -ljansson -o get_json_test
	
products_test: 
	gcc $(CFLAGS) products_test.c ../../get_json/get_json.c ../../list/list.c ../../products/product.c -lcurl -ljansson -o products_test
	
users_test: 
	gcc $(CFLAGS) users_test.c ../../get_json/get_json.c ../../list/list.c ../../users/user.c -lcurl -ljansson -o users_test
	
carts_test: 
	gcc $(CFLAGS) carts_test.c ../../get_json/get_json.c ../../list/list.c ../../carts/cart.c -lcurl -ljansson -o carts_test
	
clean:
	rm -rf *.o *.is
