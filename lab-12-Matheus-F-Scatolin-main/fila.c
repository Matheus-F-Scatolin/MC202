#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

p_fila criar_fila(void){
    //Alocar a memória da estrutura
    p_fila fila = malloc(sizeof(struct fila));
    fila->tamanho_total = MAX_VERTICES;
    //Alocar o vetor
    int * vetor = malloc(fila->tamanho_total*sizeof(struct fila));
    //Inicializar os campos da estrutura
    fila->vetor = vetor;
    fila->fim = 0;
    fila->inicio = 0;
    fila->tamanho_usado = 0;
    return fila;
}

int tem_algum_valor(p_fila fila){
    if (fila->tamanho_usado == 0)
        return 0;
    return 1;
}

void enfileirar(p_fila fila, int valor){
    //Adiconar o vaor novo
    fila->vetor[fila->fim] = valor;
    //Aumentar a posição de fim da fila
    fila->fim = (fila->fim + 1)%fila->tamanho_total;
    //Aumentar o tamanho usado
    fila->tamanho_usado+=1;
}
    
int desenfileirar(p_fila fila){
    int valor = fila->vetor[fila->inicio];
    fila->tamanho_usado-=1;
    fila->inicio = (fila->inicio + 1)%fila->tamanho_total;
    return valor;
}

void liberar_fila(p_fila fila){
    //Liberar a memória alocada para o vetor
    free(fila->vetor);
    //Liberar a memória alocada para a estrutura
    free(fila);
}