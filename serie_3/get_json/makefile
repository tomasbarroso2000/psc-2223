	
test: get_json_test.o get_json.o
	gcc -g get_json_test.o get_json.o -o test -lcurl -ljansson
	  
get_json_test.o: get_json_test.c
	gcc -g -c get_json_test.c
	
get_json.o:	get_json.c
	gcc -g -c get_json.c
	
clean:
	rm *.o 
