
memcheck: product_test.o product.o
	gcc -g product_test.c product.c ../get_json/get_json.c  ../list/list.c -o test_products -lcurl -ljansson
	valgrind --leak-check=full ./test_products

clean:
	rm -rf *.o *.is
