#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "hash_table.h"

p_hash_table criar_hash_table(){
    p_hash_table hash_table = malloc(sizeof(struct hash_table));
    hash_table->vetor = calloc(TAMANHO_VETOR, sizeof(struct familia));
    return hash_table;
}

void liberar_hash_table(p_hash_table hash_table){
    //Liberar todas as famílias que foram alocadas
    for (int i = 0; i < TAMANHO_VETOR; i ++)
        if (hash_table->vetor[i] != NULL)
            free(hash_table->vetor[i]);
    //Liberar o vetor e a hash table em si
    free(hash_table->vetor);
    free(hash_table);
}

/**
 * @brief Calcula o valor de hash para o nome de uma família usando a proporção áurea.
 *
 * @param nome_da_familia O nome da família para o qual calcular o valor de hash.
 * 
 * @return O valor de hash calculado.
 */
int hash_function(char * nome_da_familia){
    int valor = 0;
    /*passar por cada letra do nome da familia, multiplicando o valor somado
    até então pela constante da proporção áurea (1.618033988749895), sempre
    lembrando de extrair o módulo com relação ao tamanho do vetor*/
    for (int i = 0; nome_da_familia[i] != '\0'; i ++)
        valor = (((int)(valor * PROP_AUREA) + nome_da_familia[i])) % TAMANHO_VETOR;
    
    return (int)valor;
}

void inserir_na_hash_table(char * nome_da_familia, int n_doces, p_hash_table hash_table){
    //Criar a estrutura para a nova familia
    p_familia familia = malloc(sizeof(struct familia));
    //Copiar o número de doces
    familia->n_doces = n_doces;
    //Copiar o nome
    strcpy(familia->nome, nome_da_familia);

    //Colocar a familia na posição adequada
    int posicao = hash_function(familia->nome);
    int encontrou_posicao = 0;
    //Enquanto a posição não estiver vazia, ou n_doces = -1, continuar percorrendo o vetor linearmente
    //OBS: se houver uma família em alguma posição com n_doces = -1, isso significa que essa familia foi removida
    while (!encontrou_posicao){
        //Se a posição está vazia, encontramos uma posição para inserção
        if (hash_table->vetor[posicao] == NULL)
            encontrou_posicao = 1;
        //Se a posição não está vazia, mas n_doces = -1, encontramos uma posição para inserção
        else if (hash_table->vetor[posicao]->n_doces == -1)
            encontrou_posicao = 1;
        //Se não ocorrer nenhum dos dois casos anteriores, continuar procurando
        else
            posicao = (posicao + 1) % TAMANHO_VETOR;
    }


    //Se a familia atual for adicionada de forma a sobrescrever uma família que havia sido apagada, é preciso liberar memória
    if (hash_table->vetor[posicao] != NULL && hash_table->vetor[posicao]->n_doces == -1)
        free(hash_table->vetor[posicao]);
    //Finalmente, adiciona-se a família na posição correta
    hash_table->vetor[posicao] = familia;
}

int encontrar_posicao_da_familia(char * nome_da_familia, p_hash_table hash_table){
    //percorrer o vetor até encontrar a família, a partir de sua teórica posição inicial
    int posicao = hash_function(nome_da_familia);
    int encontrou_posicao = 0;

    while(!encontrou_posicao){
        //Se a familia da posição atual é a família que estamos procurando:
        if (strcmp(hash_table->vetor[posicao]->nome, nome_da_familia) == 0)
            encontrou_posicao = 1;
        //Se não, continuar procurando
        else
            posicao = (posicao + 1) % TAMANHO_VETOR;
    }
    return posicao;
}

void remover_da_hash_table(char * nome_da_familia_atual, p_hash_table hash_table){
    //Encontrar a posição da familia
    int posicao = encontrar_posicao_da_familia(nome_da_familia_atual, hash_table);

    //"Remover" a família (setar n_doces para -1)
    hash_table->vetor[posicao]->n_doces = -1;
}

int encontrar_numero_de_doces(char * nome_da_familia, p_hash_table hash_table){
    //Encontrar a família pelo seu nome:
    int posicao = encontrar_posicao_da_familia(nome_da_familia, hash_table);

    //Agora que encontramos a familia, basta retornar seu número de doces
    return hash_table->vetor[posicao]->n_doces;
}

void atualizar_na_hash_table(char * nome_da_familia_atual, int variacao_doces, p_hash_table hash_table){
    //O primeiro passo é encontrar a família pelo seu nome:
    int posicao = encontrar_posicao_da_familia(nome_da_familia_atual, hash_table);

    //Agora que encontramos a familia, basta atualizar seu número de doces
    hash_table->vetor[posicao]->n_doces += variacao_doces;
}

