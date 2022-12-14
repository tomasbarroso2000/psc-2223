
memcheck: user_test.o product.o
	gcc -g user_test.c user.c ../get_json/get_json.c  ../list/list.c -o test_users -lcurl -ljansson
	valgrind --leak-check=full ./test_users

clean:
	rm -rf *.o *.is
