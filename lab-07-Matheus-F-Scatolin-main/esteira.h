#ifndef ESTEIRA_H
#define ESTEIRA_H

#include "peca.h"

/**
 * @brief Estrutura que representa uma esteira de peças.
 */
typedef struct esteira *p_esteira;

struct esteira {
    p_peca * vetor;
    int tamanho_total, tamanho_usado, inicio, fim;
};

/**
 * @brief Cria uma esteira.
 *
 * @param tamanho_maximo O tamanho máximo da esteira.
 * @return Ponteiro para a nova esteira criada.
 */
p_esteira criar_esteira(int tamanho_maximo);

/**
 * @brief Verifica se a esteira tem espaço disponível para adicionar uma peça.
 *
 * @param esteira Ponteiro para a esteira.
 * @return 1 se há espaço disponível, 0 caso contrário.
 */
int tem_espaco(p_esteira esteira);

/**
 * @brief Verifica se a esteira possui pelo menos uma peça.
 *
 * @param esteira Ponteiro para a esteira.
 * @return 1 se há pelo menos uma peça na esteira, 0 caso contrário.
 */
int esteira_tem_peca(p_esteira esteira);

/**
 * @brief Adiciona uma peça à esteira.
 *
 * @param esteira Ponteiro para a esteira.
 * @param peca Ponteiro para a peça a ser adicionada.
 */
void adicionar_peca(p_esteira esteira, p_peca peca);

/**
 * @brief Retira uma peça da esteira, adequando sesus parâmetros no processo.
 *
 * @param esteira Ponteiro para a esteira.
 * @return Ponteiro para a peça retirada.
 */
p_peca retirar_peca(p_esteira esteira);

/**
 * @brief Libera a memória alocada para uma esteira.
 *
 * @param esteira Ponteiro para a esteira a ser liberada.
 */
void liberar_esteira(p_esteira esteira);

#endif