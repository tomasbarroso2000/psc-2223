all: libcount.so

libcount.so:
	gcc -c -fpic find.c ../../users/user.c
	gcc -shared -o libfind.so find.o user.o -ldynamic
clean:
	rm -rf *.o *.is
