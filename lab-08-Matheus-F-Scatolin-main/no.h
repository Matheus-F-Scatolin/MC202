#ifndef NO_H
#define NO_H
#include "arvore.h"

/**
 * @brief Estrutura que representa um nó da pilha.
 */
typedef struct no * p_no;

struct no{
    p_arvore arvore;
    p_no proximo;
};

#endif