#!/bin/sh

if [ -z $1 ]; then
	echo "Deve indicar um ficheiro de texto"
	exit 1;
fi

if [ -z $2 ]; then
	echo "Deve indicar a palavra a substituir (old word)"
	exit 1;
fi

if [ -z $3 ]; then
	echo "Deve indicar a palavra substituta (new word)"
	exit 1;
fi

./find_and_substitute_ref -i $1 -o $1.out.1.ref $2 $3
./find_and_substitute -i $1 -o $1.out.1 $2 $3
cmp $1.out.1 $1.out.1.ref

if [ $? -ne 0 ]; then
	exit 1;
fi

./find_and_substitute_ref -i $1 -o $1.out.2.ref -c $2 $3
./find_and_substitute -i $1 -o $1.out.2 -c $2 $3
cmp $1.out.2 $1.out.2.ref

if [ $? -ne 0 ]; then
	exit 1;
fi

./find_and_substitute_ref -i $1 -o $1.out.3.ref -w $2 $3
./find_and_substitute -i $1 -o $1.out.3 -w $2 $3
cmp $1.out.3 $1.out.3.ref

if [ $? -ne 0 ]; then
	exit 1;
fi

./find_and_substitute_ref -i $1 -o $1.out.4.ref -c -w $2 $3
./find_and_substitute -i $1 -o $1.out.4 -c -w $2 $3
cmp $1.out.4 $1.out.4.ref
if [ $? -ne 0 ]; then
	exit 1;
fi
