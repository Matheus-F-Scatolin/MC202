#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

p_pilha criar_pilha(int tamanho_maximo){
    p_pilha pilha = malloc(sizeof(struct pilha));
    pilha->tamanho_usado = 0;
    pilha->tamanho_maximo = tamanho_maximo;
    pilha->topo=NULL;
    return pilha;
}

void empilhar(p_pilha pilha, p_peca peca){
    p_no novo_no = malloc(sizeof(struct no));
    novo_no->peca = peca;
    novo_no->proximo = pilha->topo;
    pilha->topo = novo_no;
    pilha->tamanho_usado += 1;
}

int pilha_tem_peca(p_pilha pilha){
    if (pilha->tamanho_usado>0)
        return 1;
    return 0;
}

int pilha_tem_espaco(p_pilha pilha){
    int espaco = pilha->tamanho_maximo - pilha->tamanho_usado;
    if (espaco>0)
        return 1;
    return 0;
}

p_peca desempilhar(p_pilha pilha){
    p_peca peca = pilha->topo->peca;
    p_no temp = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->tamanho_usado-=1;
    return peca;
}

void liberar_pilha(p_pilha pilha){
    free(pilha);
}
