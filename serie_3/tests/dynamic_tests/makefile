CFLAGS = -c -Wall

all: libdynamic.so get_json_test products_test users_test carts_test

libdynamic.so:
	gcc -c -fpic ../../get_json/get_json.c ../../list/list.c ../../products/product.c ../../users/user.c ../../carts/cart.c
	gcc -shared -o libdynamic.so get_json.o list.o product.o user.o cart.o -lcurl -ljansson
	
get_json_test: 
	gcc get_json_test.c ../../utils.c -L. -ldynamic -ldl -lcurl -ljansson -o get_json_test
	
products_test: 
	gcc products_test.c ../../utils.c -L. -ldynamic -ldl -lcurl -ljansson -o products_test
	
users_test: 
	gcc users_test.c ../../utils.c -L. -ldynamic -ldl -lcurl -ljansson -o users_test
	
carts_test: 
	gcc carts_test.c ../../utils.c -L. -ldynamic -ldl -lcurl -ljansson -o carts_test
	
clean:
	rm -rf *.o *.is
