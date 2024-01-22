#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peca.h"
#define TAMANHO_MAXIMO 12

p_peca ler_e_criar_peca(void){
    p_peca peca = malloc(sizeof(struct peca));
    char tamanho[TAMANHO_MAXIMO];

    int tipo;
    scanf(" %s", tamanho);
    scanf(" %d", &tipo);
    if (strcmp(tamanho, "grande") == 0){
        peca->tempo_classificar = 3;
        if (tipo == 1)
            peca->tempo_embalar = 2;
        else 
            peca->tempo_embalar = 3;
    }
    else if (strcmp(tamanho, "media") == 0){
        peca->tempo_classificar = 2;
        if (tipo == 1)
            peca->tempo_embalar = 2;
        else
            peca->tempo_embalar = 3;
    }

    else {
        peca->tempo_classificar = 1;
        if (tipo == 1)
            peca->tempo_embalar = 1;
        else 
            peca->tempo_embalar = 2;
    }


    return peca;
}

void liberar_peca(p_peca peca){
    free(peca);
}
