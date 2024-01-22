#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pedido.h"
#define MAX_ID 10

//Dada uma linha de código, essa função retorna o pedido correspondente
p_pedido criar_pedido(char * linha, p_sobrevivente * v_sobreviventes){
    //Ex de linha: "novo 0 Creamy n Purée" (novo <ID> <PRATO>)
    p_pedido pedido = malloc(sizeof(struct pedido));

    char id[MAX_ID];
    char prato[MAX_PRATO];

    //Os caracteres até a posição 4 (inclusive) do input não nos interessam
    int pos_atual = 5;
    //enquanto não chegar no espaço que separa o <ID> e o <PRATO>, continuar lendo o ID
    for (pos_atual = 5; linha[pos_atual] != ' '; pos_atual++){
        id[pos_atual-5] = linha[pos_atual];
    }
    id[pos_atual-5] = '\0';
    pedido->id = atoi(id);
    
    //Pular o espaço
    pos_atual ++;
    int inicio_prato = pos_atual;
    //Começar a ler o nome do prato
    for (; linha[pos_atual] != '\0'; pos_atual++){
        prato[pos_atual-inicio_prato] = linha[pos_atual];
    }
    prato[pos_atual-inicio_prato] = '\0';
    strcpy(pedido->prato, prato);

    //Descobrir a prioridade do pedido
    pedido->prioridade = v_sobreviventes[pedido->id]->dias_sobrevividos;
    //Fazer com que o campo "pedido_atual" do sobrevivente aponte para esse pedido
    v_sobreviventes[pedido->id]->pedido_atual = pedido;

    return pedido;
}

char * quem_pediu(p_sobrevivente * v_sobreviventes, p_pedido pedido){
    return v_sobreviventes[pedido->id]->nome;
}

char * nome_prato(p_pedido pedido){
    return pedido->prato;
}

int descobrir_prioridade(p_pedido pedido){
    return pedido->prioridade;
}

void liberar_pedido(p_pedido pedido, p_sobrevivente * v_sobreviventes){
    //Voltar o campo "pedido_atual" do sobrevivente para NULL
    v_sobreviventes[pedido->id]->pedido_atual = NULL;
    //Liberar a memória alocada para o pedido
    free(pedido);
}
