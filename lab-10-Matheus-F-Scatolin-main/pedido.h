#ifndef PEDIDO_H
#define PEDIDO_H
#include "sobrevivente.h"
#define MAX_PRATO 30

typedef struct pedido* p_pedido;
typedef struct sobrevivente* p_sobrevivente;


struct pedido{
    int id, prioridade;
    char prato[MAX_PRATO];
    //Indica a posição atual do pedido na fila de prioridades
    int pos_na_f_prio;
};

/**
 * @brief Cria um novo pedido a partir de uma linha de texto e do vetor de sobreviventes.
 *
 * @param linha A linha de texto contendo informações do pedido.
 * @param v_sobreviventes O vetor de sobreviventes.
 * 
 * @return Um ponteiro para a estrutura de pedido criada.
 */
p_pedido criar_pedido(char * linha, p_sobrevivente * v_sobreviventes);

/**
 * @brief Descobre o nome do sobrevivente que fez o pedido.
 *
 * @param v_sobreviventes O vetor de sobreviventes.
 * @param pedido O pedido cujo sobrevivente será identificado.
 * 
 * @return O nome do sobrevivente que fez o pedido.
 */
char * quem_pediu(p_sobrevivente * v_sobreviventes, p_pedido pedido);

/**
 * @brief Descobre o nome do prato do pedido.
 *
 * @param pedido O pedido do qual o prato será obtido.
 * 
 * @return O nome do prato do pedido.
 */
char * nome_prato(p_pedido pedido);

/**
 * @brief Descobre a prioridade atual do pedido.
 *
 * @param pedido O pedido do qual a prioridade será obtida.
 * 
 * @return A prioridade atual do pedido.
 */
int descobrir_prioridade(p_pedido pedido);

/**
 * @brief Libera a memória alocada para um pedido e atualiza o campo "pedido_atual" do sobrevivente.
 *
 * @param pedido O pedido a ser liberado.
 * @param v_sobreviventes O vetor de sobreviventes.
 */
void liberar_pedido(p_pedido pedido, p_sobrevivente * v_sobreviventes);

#endif