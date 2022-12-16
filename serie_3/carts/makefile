
test: cart_test.o cart.o
	gcc -g -Wall cart_test.c cart.c ../get_json/get_json.c  ../list/list.c -o test_carts -lcurl -ljansson

clean:
	rm -rf *.o *.is
