#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "peca.h"

/**
 * @brief Estrutura que representa um funcionário.
 */
typedef struct funcionario *p_funcionario;


struct funcionario {
    int tempo_total_peca;
    int progresso;
    p_peca peca_atual;
    //Tipo 1: classificador, tipo 2: embalador
    int tipo;
};

/**
 * @brief Cria um funcionário.
 *
 * @param tipo_do_funcionario O tipo do funcionário (1 para classificador, 2 para embalador).
 * @return Ponteiro para o novo funcionário criado.
 */
p_funcionario criar_funcionario(int tipo_do_funcionario);

/**
 * @brief Verifica se o funcionário está livre (sem uma peça para processar).
 *
 * @param funcionario Ponteiro para o funcionário.
 * @return 1 se o funcionário está livre, 0 caso contrário.
 */
int esta_livre(p_funcionario funcionario);

/**
 * @brief Define a peça que o funcionário está processando.
 *
 * @param funcionario Ponteiro para o funcionário.
 * @param peca Ponteiro para a peça a ser processada.
 */
void pegar_peca(p_funcionario funcionario, p_peca peca);

/**
 * @brief "Passa" a peça que o funcionário estava processando.
 * A função faz com que a peca que o funcionario estava segurando seja
 * retornada, e ele passa a não segurar nada (NULL).
 *
 * @param funcionario Ponteiro para o funcionário.
 * @return Ponteiro para a peça que o funcionário estava processando.
 */
p_peca passar_a_peca(p_funcionario funcionario);

/**
 * @brief Contabiliza um minuto de trabalho para o funcionário na peça atual.
 *
 * @param funcionario Ponteiro para o funcionário.
 */
void contar_minuto(p_funcionario funcionario);

/**
 * @brief Retorna o número de minutos restantes para o funcionário terminar de processar a peça.
 *
 * @param funcionario Ponteiro para o funcionário.
 * @return Número de minutos restantes ou -1 se o funcionário estiver livre.
 */
int mostrar_minutos_restantes(p_funcionario funcionario);

/**
 * @brief Libera a memória alocada para um funcionário.
 *
 * @param funcionario Ponteiro para o funcionário a ser liberado.
 */
void liberar_funcionario(p_funcionario funcionario);

#endif