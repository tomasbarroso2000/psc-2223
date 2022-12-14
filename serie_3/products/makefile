
test: product_test.o product.o
	gcc -g -Wall product_test.c product.c ../get_json/get_json.c  ../list/list.c -o test_products -lcurl -ljansson

clean:
	rm -rf *.o *.is
