CC = gcc
CFLAGS = -Wall -Werror -g

all: clean redecomep

redecomep: redecomep.o grafo.o fila.o
	$(CC) $(CFLAGS) -o redecomep redecomep.o grafo.o fila.o

redecomep.o: redecomep.c
	$(CC) $(CFLAGS) -c redecomep.c

grafo.o: grafo.c grafo.h
	$(CC) $(CFLAGS) -c grafo.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

clean:
	rm -f *.o redecomep