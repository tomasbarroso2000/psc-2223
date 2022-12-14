		
all: libjson.a

test: get_json_test.o get_json.o
	gcc -g -Wall get_json_test.o get_json.o -o test_get_json -lcurl -ljansson

libjson.a: get_json.o
	ar -rcs libjson.a get_json.o

get_json.o: get_json.c get_json.h
	gcc -c -Wall get_json.c -o get_json.o -Wall

clean:
	rm -rf *.o *.is
