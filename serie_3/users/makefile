
test: user_test.o user.o
	gcc -g -Wall user_test.c user.c ../get_json/get_json.c  ../list/list.c -o test_users -lcurl -ljansson

clean:
	rm -rf *.o *.is
