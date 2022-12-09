
all: liblist.a

liblist.a: list.o
	ar -rcs liblist.a list.o

list.o: list.c list.h
	gcc -c list.c -o list.o -Wall

clean:
	rm -rf *.o *.is
