CC = gcc
CFLAGS = -Wall -Werror -g

all: clean halloween

halloween: halloween.o hash_table.o
	$(CC) $(CFLAGS) -o halloween halloween.o hash_table.o

halloween.o: halloween.c
	$(CC) $(CFLAGS) -c halloween.c

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

clean:
	rm -f *.o halloween