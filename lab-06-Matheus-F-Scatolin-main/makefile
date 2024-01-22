CC = gcc
CFLAGS = -Wall -Werror -g

all: clean livros

livros: livros.o lista_livros.o
	$(CC) $(CFLAGS) -o livros livros.o lista_livros.o

livros.o: livros.c lista_livros.h
	$(CC) $(CFLAGS) -c livros.c

lista_livros.o: lista_livros.c lista_livros.h
	$(CC) $(CFLAGS) -c lista_livros.c

clean:
	rm -f *.o livros