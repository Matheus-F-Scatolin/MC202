#ifndef FAMILIA_H
#define FAMILIA_H
#define MAX_NOME 11

typedef struct familia * p_familia;

struct familia{
    char nome[MAX_NOME];
    //Se n_doces = -1, isso indica que a posição está vazia
    int n_doces;
};

#endif