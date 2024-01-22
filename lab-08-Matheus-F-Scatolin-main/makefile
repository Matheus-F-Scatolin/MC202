CC = gcc
CFLAGS = -Wall -Werror -g

all: clean expressoes

expressoes: expressoes.o arvore.o pilha.o
	$(CC) $(CFLAGS) -o expressoes expressoes.o arvore.o pilha.o

expressoes.o: expressoes.c arvore.h pilha.h
	$(CC) $(CFLAGS) -c expressoes.c

arvore.o: arvore.c arvore.h
	$(CC) $(CFLAGS) -c arvore.c

pilha.o: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

clean:
	rm -f *.o expressoes