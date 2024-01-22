CC = gcc
CFLAGS = -Wall -Werror -g

all: clean simulador

simulador: simulador.o peca.o esteira.o pilha.o funcionario.o
	$(CC) $(CFLAGS) -o simulador simulador.o peca.o esteira.o pilha.o funcionario.o

simulador.o: simulador.c peca.h esteira.h pilha.h funcionario.h
	$(CC) $(CFLAGS) -c simulador.c

peca.o: peca.c peca.h
	$(CC) $(CFLAGS) -c peca.c

esteira.o: esteira.c esteira.h
	$(CC) $(CFLAGS) -c esteira.c

pilha.o: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

funcionario.o: funcionario.c funcionario.h
	$(CC) $(CFLAGS) -c funcionario.c

clean:
	rm -f *.o simulador