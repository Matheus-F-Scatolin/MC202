#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peca.h"
#include "funcionario.h"

p_funcionario criar_funcionario(int tipo_do_funcionario){
    p_funcionario funcionario = malloc(sizeof(struct funcionario));
    funcionario->tipo = tipo_do_funcionario;
    funcionario->peca_atual=NULL;
    funcionario->progresso=0;
    funcionario->tempo_total_peca=0;
    return funcionario;
}

int esta_livre(p_funcionario funcionario){
    if (funcionario->peca_atual==NULL)
        return 1;
    return 0;
}

void pegar_peca(p_funcionario funcionario, p_peca peca){
    funcionario->progresso = 0;
    funcionario->peca_atual = peca;
    if (funcionario->tipo == 1)
        funcionario->tempo_total_peca = peca->tempo_classificar;
    else
        funcionario->tempo_total_peca = peca->tempo_embalar;
}

p_peca passar_a_peca(p_funcionario funcionario){
    p_peca peca = funcionario->peca_atual;
    funcionario->peca_atual = NULL;
    return peca;
}

int mostrar_minutos_restantes(p_funcionario funcionario){
    int progresso = funcionario->progresso;
    int total = funcionario->tempo_total_peca;
    //Se o funcionario estiver sem peça, retorna -1
    if (esta_livre(funcionario))
        return -1;
    if (total-progresso<0)
        return 0;
    return (total-progresso);
}

void contar_minuto(p_funcionario funcionario){
    funcionario->progresso+=1;
}

void liberar_funcionario(p_funcionario funcionario){
    free(funcionario);
}
