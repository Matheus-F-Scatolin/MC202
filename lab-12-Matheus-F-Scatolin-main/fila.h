#ifndef FILA_H
#define FILA_H
#include "grafo.h"

typedef struct fila *p_fila;

//Implementção da fila com um vetor circular
struct fila {
    int * vetor;
    int tamanho_total, tamanho_usado, inicio, fim;
};

/**
 * @brief Cria uma fila.
 *
 * @return Ponteiro para a nova fila criada.
 */
p_fila criar_fila(void);


/**
 * @brief Verifica se a fila possui pelo menos um valor.
 *
 * @param fila Ponteiro para a fila.
 * @return 1 se há pelo menos um valor na fila, 0 caso contrário.
 */
int tem_algum_valor(p_fila fila);

/**
 * @brief Adiciona um valor à fila.
 *
 * @param fila Ponteiro para a fila.
 * @param valor Valor a ser adicionado.
 */
void enfileirar(p_fila fila, int valor);

/**
 * @brief Retira um valor da fila.
 *
 * @param fila Ponteiro para a fila.
 * @return O valor retirado.
 */
int desenfileirar(p_fila fila);

/**
 * @brief Libera a memória alocada para uma fila.
 *
 * @param fila Ponteiro para a fila a ser liberada.
 */
void liberar_fila(p_fila fila);

#endif