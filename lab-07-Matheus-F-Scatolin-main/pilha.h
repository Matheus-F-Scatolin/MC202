#ifndef PILHA_H
#define PILHA_H

#include "no.h"
#include "peca.h"

/**
 * @brief Estrutura que representa uma pilha de peças.
 */
typedef struct pilha *p_pilha;

struct pilha {
    p_no topo;
    int tamanho_usado;
    int tamanho_maximo;
};

/**
 * @brief Cria uma nova pilha.
 *
 * @param tamanho_maximo O tamanho máximo da pilha.
 * @return Ponteiro para a nova pilha criada.
 */
p_pilha criar_pilha(int tamanho_maximo);

/**
 * @brief Verifica se a pilha possui pelo menos uma peça.
 *
 * @param pilha Ponteiro para a pilha.
 * @return 1 se a pilha possui pelo menos uma peça, 0 caso contrário.
 */
int pilha_tem_peca(p_pilha pilha);

/**
 * @brief Verifica se a pilha tem espaço disponível para adicionar uma peça.
 *
 * @param pilha Ponteiro para a pilha.
 * @return 1 se a pilha tem espaço disponível, 0 caso contrário.
 */
int pilha_tem_espaco(p_pilha pilha);

/**
 * @brief Empilha uma peça na pilha. No processo, cria um nó para colocar
 * a peça e coloca esse nó no topo da pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @param peca Ponteiro para a peça a ser empilhada.
 */
void empilhar(p_pilha pilha, p_peca peca);

/**
 * @brief Desempilha uma peça da pilha. No processo, a função libera
 * o nó do elemento desempilhado e reduz o tamanho usado da pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Ponteiro para a peça desempilhada.
 */
p_peca desempilhar(p_pilha pilha);

/**
 * @brief Libera a memória alocada para uma pilha.
 *
 * @param pilha Ponteiro para a pilha a ser liberada.
 */
void liberar_pilha(p_pilha pilha);

#endif