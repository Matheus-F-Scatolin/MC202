#ifndef PECA_H
#define PECA_H

/**
 * @brief Estrutura que representa uma peça a ser processada.
 */
typedef struct peca *p_peca;

struct peca{
    int tempo_classificar, tempo_embalar;
};

/**
 * @brief Lê e cria uma nova peça.
 *
 * @return Ponteiro para a nova peça criada.
 */
p_peca ler_e_criar_peca(void);

/**
 * @brief Libera a memória alocada para uma peça.
 *
 * @param peca Ponteiro para a peça a ser liberada.
 */
void liberar_peca(p_peca peca);

#endif