CC = gcc
CFLAGS = -Wall -Werror -g

all: clean dracarys

dracarys: dracarys.o arvore.o
	$(CC) $(CFLAGS) -o dracarys dracarys.o arvore.o

dracarys.o: dracarys.c
	$(CC) $(CFLAGS) -c dracarys.c

arvore.o: arvore.c arvore.h
	$(CC) $(CFLAGS) -c arvore.c

clean:
	rm -f *.o dracarys