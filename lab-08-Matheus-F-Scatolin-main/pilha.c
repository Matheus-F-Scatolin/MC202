#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "no.h"

p_pilha criar_pilha(void){
    p_pilha pilha = malloc(sizeof(struct pilha));
    pilha->topo=NULL;
    pilha->tamanho = 0;
    return pilha;
}

int ver_tamanho(p_pilha pilha){
    return pilha->tamanho;
}

void empilhar(p_pilha pilha, p_arvore arvore){
    p_no novo = malloc(sizeof(struct no));
    novo->arvore = arvore;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho += 1;
}

p_arvore desempilhar(p_pilha pilha){
    p_no temp = pilha->topo;
    p_arvore arvore = temp->arvore;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->tamanho -= 1;
    return arvore;
}

void liberar_pilha(p_pilha pilha){
    free(pilha);
}