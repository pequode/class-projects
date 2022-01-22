CC=gcc -Wall -g

all: threads main.c
	$(CC) -o main main.c threads.o
	$(CC) -Wall -Werror -O0 -g main.c threads.o -o main 
	./main

threads: threads.c
	$(CC) -c -o threads.o threads.c


clean:
	rm main threads.o
