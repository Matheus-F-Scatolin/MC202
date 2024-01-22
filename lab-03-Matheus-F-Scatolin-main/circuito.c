#include <stdlib.h>
#include <stdio.h>
#include "circuito.h"

/*
Dado um número de participantes, essa função
lê as informações de um circuito e devolve o
circuito.
*/
circuito ler_circuito(int n_participantes){
    circuito circ;
    circ.n_participantes = n_participantes;
    circ.jogadas = malloc(n_participantes*sizeof(int));
    scanf(" %d", &circ.identificacao);

    if (circ.jogadas == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    for (int c=0; c<n_participantes; c++){
        scanf(" %d", &circ.jogadas[c]);
    }

    return circ;
}