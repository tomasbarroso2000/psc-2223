CFLAGS = -c -Wall

all: libdynamic.so products_test users_test

libdynamic.so:
	gcc -c -fpic ../../get_json/get_json.c ../../list/list.c ../../products/product.c ../../users/user.c ../../carts/cart.c
	gcc -shared -o libdynamic.so get_json.o list.o product.o user.o cart.o -lcurl -ljansson
	
products_test: 
	gcc products_test.c -L. -ldynamic -ldl -lcurl -ljansson -o products_test
	
users_test: 
	gcc users_test.c -L. -ldynamic -ldl -lcurl -ljansson -o users_test
	
clean:
	rm -rf *.o *.is
