CC = gcc
CFLAGS	= -Wall -Werror -O0 -g 
need = -std=c99 -pthread

all:
	$(CC) $(CFLAGS) sandbox.c -o cthread
	./cthread
	
clean: 
	rm cthread
