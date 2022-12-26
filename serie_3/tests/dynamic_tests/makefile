
#export LD_LIBRARY_PATH=/home/aluno/Documents/PSC-2223SI/serie_3/tests/:$LD_LIBRARY_PATH

#dynamic lib
libjson.so: product.c
	gcc -c -fpic ../../products/product.c
	gcc -shared -o dynamiclib.so product.o
	
product.c: 
	gcc -c -Wall ../../products/product.c -o product.o -fpic

clean:
	rm -rf *.o *.is
