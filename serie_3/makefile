
all: app

app:
	gcc -g app.c command.c data.c ../utils.c -ldynamic -ldl -lcurl -ljansson -o app

clean:
	rm -rf *.o *.is
