#ifndef NO_H
#define NO_H
#include "peca.h"

/**
 * @brief Estrutura que representa um nó.
 */
typedef struct no * p_no;

struct no{
    p_peca peca;
    p_no proximo;
};

#endif