#ifndef SOBREVIVENTE_H
#define SOBREVIVENTE_H
#include "pedido.h"
#define MAX_NOME 50

typedef struct sobrevivente* p_sobrevivente;
typedef struct pedido* p_pedido;


struct sobrevivente{
    int id, dias_sobrevividos;
    char nome[MAX_NOME];
    /*Ponteiro para o pedido atual do sobrevivente.
    Se ele não tiver feito nenhum pedido, aponta para NULL*/
    p_pedido pedido_atual;
};

/**
 * @brief Lê as informações de um sobrevivente a partir de uma linha de texto.
 *
 * @param id O ID do sobrevivente.
 * 
 * @return Um ponteiro para a estrutura de sobrevivente criada.
 */
p_sobrevivente ler_sobrevivente(int id);

/**
 * @brief Libera a memória alocada para cada um dos sobreviventes de um vetor
 * de sobreviventes.
 *
 * @param pedido O pedido a ser liberado.
 * @param v_sobreviventes O vetor de sobreviventes.
 */
void liberar_sobreviventes(p_sobrevivente * v_sobreviventes, int n_sobreviventes);

#endif