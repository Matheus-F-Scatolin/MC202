#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pedido.h"
#include "sobrevivente.h"
#define MAX_LINHA 100
#define MAX_DIAS 8

p_sobrevivente ler_sobrevivente(int id){
    p_sobrevivente sobrevivente = malloc(sizeof(struct sobrevivente));
    char linha_de_texto[MAX_LINHA], nome[MAX_NOME], n_dias[MAX_DIAS];
    fgets(linha_de_texto, MAX_LINHA, stdin);
    //Ex de linha: Wolfgang Strongman 1080
    int contador_espaco = 0;
    //Percorrer a linha até o segundo espaço, copiando o nome para a variável 'nome'
    int pos_atual = 0;
    for (pos_atual = 0; pos_atual < MAX_LINHA; pos_atual ++){
        if (linha_de_texto[pos_atual] == ' ')
            contador_espaco ++;
        if (contador_espaco == 2)
            break;
        nome[pos_atual] = linha_de_texto[pos_atual];
    }
    //Colocar um '\0' no fim do nome
    nome[pos_atual] = '\0';

    //Pular o segundo espaço
    pos_atual += 1;
    int inicio_dias = pos_atual;
    //Copiar o resto da linha para a variavel 'n_dias'
    for(; linha_de_texto[pos_atual] != '\0'; pos_atual ++){
        n_dias[pos_atual - inicio_dias] = linha_de_texto[pos_atual];
    }

    //Fazer as atribuições corretas
    strcpy(sobrevivente->nome, nome);
    sobrevivente->dias_sobrevividos = atoi(n_dias);
    sobrevivente->id = id;
    //Ponteiro para o pedido atual aponta para NULL por padrão
    sobrevivente->pedido_atual = NULL;
    
    return sobrevivente;
}

void liberar_sobreviventes(p_sobrevivente * v_sobreviventes, int n_sobreviventes){
    for (int i = 0; i < n_sobreviventes; i ++){
        free(v_sobreviventes[i]);
    }
}
