CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
OBJ = main.o

main: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean
clean:
	rm $(OBJ) main
