#ifndef CIRCUITO_H
#define CIRCUITO_H

typedef struct _circuito {
    int identificacao, n_participantes, *jogadas;
} circuito;

circuito ler_circuito(int n_participantes);

#endif