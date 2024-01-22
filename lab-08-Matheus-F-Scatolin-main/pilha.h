#ifndef PILHA_H
#define PILHA_H
#include "no.h"

typedef struct pilha * p_pilha;

/**
 * @brief Estrutura para representar o topo da pilha e seu tamanho.
 */
struct pilha{
    p_no topo;
    int tamanho;
};

/**
 * @brief Cria uma nova pilha vazia.
 *
 * @return Ponteiro para a nova pilha criada.
 */
p_pilha criar_pilha(void);

/**
 * @brief Retorna o tamanho da pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Tamanho da pilha.
 */
int ver_tamanho(p_pilha pilha);

/**
 * @brief Empilha uma árvore na pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @param arvore Ponteiro para a árvore a ser empilhada.
 */
void empilhar(p_pilha pilha, p_arvore arvore);

/**
 * @brief Desempilha uma árvore da pilha, liberando o nó
 * associado à arvore no processo.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Ponteiro para a árvore desempilhada.
 */
p_arvore desempilhar(p_pilha pilha);

/**
 * @brief Libera a memória ocupada pela pilha.
 *
 * @param pilha Ponteiro para a pilha a ser liberada.
 */
void liberar_pilha(p_pilha pilha);

#endif