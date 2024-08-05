# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = circular_buffer.o main.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

circular_buffer.o: circular_buffer.c circular_buffer.h
	$(CC) $(CFLAGS) -c circular_buffer.c

main.o: main.c circular_buffer.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o main
