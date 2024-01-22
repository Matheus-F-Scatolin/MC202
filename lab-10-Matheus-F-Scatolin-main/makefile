CC = gcc
CFLAGS = -Wall -Werror -g

all: clean cozinha

cozinha: cozinha.o sobrevivente.o pedido.o fila_prioridades.o
	$(CC) $(CFLAGS) -o cozinha cozinha.o sobrevivente.o pedido.o fila_prioridades.o

cozinha.o: cozinha.c sobrevivente.h pedido.h fila_prioridades.h
	$(CC) $(CFLAGS) -c cozinha.c

sobrevivente.o: sobrevivente.c sobrevivente.h
	$(CC) $(CFLAGS) -c sobrevivente.c

pedido.o: pedido.c pedido.h
	$(CC) $(CFLAGS) -c pedido.c

fila_prioridades.o: fila_prioridades.c fila_prioridades.h
	$(CC) $(CFLAGS) -c fila_prioridades.c

clean:
	rm -f *.o cozinha