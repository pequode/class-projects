CC=gcc -Werror -Wall -g

all: tls.c main.c
	$(CC) -c -o tls.o tls.c
	gcc -Werror -Wall -o main -lpthread  main.c tls.o
	./main
Tests: tls.c creator_cloner_test.c 
	$(CC) -c -o tls.o tls.c
	gcc -Wall -Werror -o main tls.o -lpthread creator_cloner_test.c
	./main
clean:
	rm main  tls.o
