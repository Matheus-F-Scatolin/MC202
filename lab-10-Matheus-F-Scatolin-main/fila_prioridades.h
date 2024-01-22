#ifndef FILA_PRIORIDADES_H
#define FILA_PRIORIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"


typedef struct fila_de_prioridade * p_fila_de_prioridade;

struct fila_de_prioridade {
    int tamanho;
    p_pedido * vetor;
};

/**
 * @brief Cria uma nova fila de prioridades com base no número de sobreviventes.
 *
 * @param n_sobreviventes O número de sobreviventes.
 * 
 * @return Um ponteiro para a fila de prioridades criada.
 */
p_fila_de_prioridade criar_fila(int n_sobreviventes);

/**
 * @brief Efetua a troca entre 2 posições na fila de prioridades,
 * e atualia os campos "pos_na_f_prio" dos pedidos no processo.
 * 
 * @param pedido_1 Ponteiro para o 1º pedido a ser trocado.
 * @param pedido_2 Ponteiro para o pedido que vai trocar de lugar com o primeiro.
*/
void troca(p_pedido * pedido_1, p_pedido * pedido_2);

/**
 * @brief Encontra o tamanho atual da fila de prioridades.
 *
 * @param fila A fila de prioridades.
 * 
 * @return O tamanho atual da fila de prioridades.
 */
int tamanho_da_fila(p_fila_de_prioridade fila);

/**
 * @brief Encontra o maior filho de um nó na fila de prioridades.
 *
 * @param fila A fila de prioridades.
 * @param posicao A posição do nó.
 * 
 * @return A posição do maior filho do nó especificado ou -1 se o nó não tiver filhos.
 */
int encontrar_maior_filho(p_fila_de_prioridade fila, int posicao);

/**
 * @brief Move um nó para baixo na fila de prioridades para reorganizá-la.
 *
 * @param fila A fila de prioridades.
 * @param posicao A posição do nó a ser movido.
 */
void desce_no_heap(p_fila_de_prioridade fila, int posicao);

/**
 * @brief Extrai o pedido com a maior prioridade da fila de prioridades.
 *
 * @param fila A fila de prioridades.
 * 
 * @return Um ponteiro para o pedido extraído.
 */
p_pedido extrair_pedido(p_fila_de_prioridade fila);

/**
 * @brief Move um nó para cima na fila de prioridades para reorganizá-la.
 *
 * @param fila A fila de prioridades.
 * @param pos_insercao A posição do nó a ser movido para cima.
 */
void sobe_no_heap(p_fila_de_prioridade fila, int pos_insercao);

/**
 * @brief Insere um novo pedido na fila de prioridades e reorganiza ela conforme necessário.
 *
 * @param novo_pedido O novo pedido a ser inserido.
 * @param fila A fila de prioridades.
 */
void inserir_novo_pedido(p_pedido novo_pedido, p_fila_de_prioridade fila);

/**
 * @brief Altera a prioridade de um pedido e reorganiza a fila de prioridades conforme necessário.
 *
 * @param fila A fila de prioridades.
 * @param sob_que_pediu O sobrevivente que fez o pedido.
 * @param variacao_da_prioridade A variação da prioridade do pedido.
 */
void alterar_prioridade(p_fila_de_prioridade fila, p_sobrevivente sob_que_pediu, int variacao_da_prioridade);

/**
 * @brief Libera a memória alocada para a fila de prioridades.
 *
 * @param fila Ponteiro para a fila.
 */
void liberar_fila(p_fila_de_prioridade fila);

#endif