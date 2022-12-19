
dynamic_lib.so: product.o user.o cart.o
	gcc -shared -o dynamic_lib.so product.o user.o cart.o list.o get_json.o -Wall
	
product.o: products/product.c get_json/get_json.o list/list.o
	gcc -g -c products/product.c get_json/get_json.c list/list.c -lcurl -ljansson -fpic -Wall
	
user.o: users/user.c get_json/get_json.o list/list.o
	gcc -g -c users/user.c get_json/get_json.c list/list.c -lcurl -ljansson -fpic -Wall
	
cart.o: carts/cart.c get_json/get_json.o list/list.o
	gcc -g -c carts/cart.c get_json/get_json.c list/list.c -lcurl -ljansson -fpic -Wall
	
get_json.o: get_json/get_json.c
	gcc -g -c get_json/get_json.c -fpic -Wall
	
list.o: list/list.c
	gcc -g -c list.c -fpic -Wall
	
clean:
	rm -rf *.o *.is
