#include <stdio.h>
#include <stdlib.h>
#include "peca.h"
#include "esteira.h"

p_esteira criar_esteira(int tamanho_maximo){
    p_esteira esteira = malloc(sizeof(struct esteira));
    esteira->tamanho_total = tamanho_maximo;
    p_peca * vetor = malloc(esteira->tamanho_total*sizeof(struct peca));
    esteira->vetor = vetor;
    esteira->fim = 0;
    esteira->inicio = 0;
    esteira->tamanho_usado = 0;
    return esteira;
}

int esteira_tem_peca(p_esteira esteira){
    if (esteira->tamanho_usado == 0)
        return 0;
    return 1;
}

void adicionar_peca(p_esteira esteira, p_peca peca){
    esteira->vetor[esteira->fim] = peca;
    esteira->fim = (esteira->fim + 1)%esteira->tamanho_total;
    esteira->tamanho_usado+=1;
}

int tem_espaco(p_esteira esteira){
    int espaco = esteira->tamanho_total - esteira->tamanho_usado;
    if (espaco>0)
        return 1;
    return 0;
}
    
p_peca retirar_peca(p_esteira esteira){
    p_peca peca = esteira->vetor[esteira->inicio];
    esteira->tamanho_usado-=1;
    esteira->inicio = (esteira->inicio + 1)%esteira->tamanho_total;
    return peca;
}

void liberar_esteira(p_esteira esteira){
    free(esteira->vetor);
    free(esteira);
}
