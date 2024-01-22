#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "hash_table.h"
#define MAX_COMANDO 15
#define MAX_NOME 11
#define MAX_NOTA 10
enum tipo_de_comando {ENTRAR, SAIR, COMPRAR, TRICKORTREAT, FINALIZAR};

/**
 * @brief Lê um comando de entrada e retorna o tipo correspondente.
 *
 * @return O tipo de comando lido (ENTRAR, SAIR, COMPRAR, TRICKORTREAT ou FINALIZAR).
 */
enum tipo_de_comando ler_tipo_comando(){
    char comando[MAX_COMANDO];
    scanf(" %s", comando);
    if (strcmp(comando, "ENTRAR") == 0)
        return ENTRAR;
    if (strcmp(comando, "SAIR") == 0)
        return SAIR;
    if (strcmp(comando, "COMPRAR") == 0)
        return COMPRAR;
    if (strcmp(comando, "TRICKORTREAT") == 0)
        return TRICKORTREAT;
    return FINALIZAR;
}

/**
 * @brief Determina a quantidade de doces que uma criança deve receber com base na nota
 * da família e na quantidade de doces disponíveis.
 *
 * @param max_doces A quantidade máxima de doces que a família pode fornecer.
 * 
 * @return A quantidade de doces a serem recebidos pela criança.
 */
int doces_a_serem_recebidos(int max_doces){
    char nota[MAX_NOTA];
    int doces_a_serem_recebidos = 0;
    //Ler a nota que a familia deu para a criança
    scanf(" %s", nota);
    //Ver quantos doces a criança deveria receber
    if (strcmp(nota, "Boa") == 0)
        doces_a_serem_recebidos = 3;
    else if (strcmp(nota, "Media") == 0)
        doces_a_serem_recebidos = 2;
    else if (strcmp(nota, "Ruim") == 0)
        doces_a_serem_recebidos = 1;

    //Se a família tiver doces o suficiente, ela dá o que a criança deveria receber
    if (max_doces >= doces_a_serem_recebidos)
        return doces_a_serem_recebidos;
    //Se a família não tiver doces o suficiente, ela dá o máximo possível
    else
        return max_doces;
}

int main(){
    char nome_da_familia_atual[MAX_NOME];
    char nome_da_crianca[MAX_NOME];
    char sobrenome_da_crianca[MAX_NOME];
    int n_doces = 0, n_casas = 0, max_doces = 0, total_de_doces_recebidos = 0, doces_restantes = 0;
    //Criar uma hash_table para guardar as famílias
    p_hash_table hash_table = criar_hash_table();

    //Começar um loop para executar uma das funções: entrar, sair, comprar, trickortreat ou finalizar
    enum tipo_de_comando tipo_comando_atual;
    tipo_comando_atual = ler_tipo_comando();
    while (tipo_comando_atual != FINALIZAR){
        if (tipo_comando_atual == ENTRAR){
            //Ler o nome da família e a quatidade de doces que ela possui
            scanf(" %s", nome_da_familia_atual);
            scanf(" %d", &n_doces);

            //Inserir a familia na hash table
            inserir_na_hash_table(nome_da_familia_atual, n_doces, hash_table);
        }

        else if (tipo_comando_atual == SAIR){
            //Ler o nome da família que vai sair e remover ela da hash table
            scanf(" %s", nome_da_familia_atual);

            //Descobrir quantos doces a familia ainda tinha e removê-la
            doces_restantes = encontrar_numero_de_doces(nome_da_familia_atual, hash_table);
            remover_da_hash_table(nome_da_familia_atual, hash_table);

            //Imprimir o resultado: "A familia <Nome da Família> saiu com <Qtd de Doces> doce(s) sobrando."
            printf("A familia %s saiu com %d doce(s) sobrando.\n", nome_da_familia_atual, doces_restantes);
        }


        else if (tipo_comando_atual == COMPRAR){
            //Ler o nome da família e a quatidade de doces que ela vai comprar
            scanf(" %s", nome_da_familia_atual);
            scanf(" %d", &n_doces);
            //Atualizar a quantidade de doces
            atualizar_na_hash_table(nome_da_familia_atual, n_doces, hash_table);

            //Imprimir resultado: "A familia <Nome da Família> agora possui <Qtd de Doces> doces."
            doces_restantes = encontrar_numero_de_doces(nome_da_familia_atual, hash_table);
            printf("A familia %s agora possui %d doces.\n", nome_da_familia_atual, doces_restantes);
        }

        else if (tipo_comando_atual == TRICKORTREAT){
            //Ler o nome e o sobrenome da criança
            scanf(" %s", nome_da_crianca);
            scanf(" %s", sobrenome_da_crianca);
            //Ler o número de casas
            scanf(" %d", &n_casas);
            //Iniciar o loop para que cada casa dê a nota e os doces à criança
            total_de_doces_recebidos = 0;
            for (int i = 0; i < n_casas; i ++){
                //Ler o nome da família
                scanf(" %s", nome_da_familia_atual);
                //Encontrar q quantidade de doces a família possui
                max_doces = encontrar_numero_de_doces(nome_da_familia_atual, hash_table);

                //Descobrir quantos doces a criança irá receber a partir da nota
                n_doces = doces_a_serem_recebidos(max_doces);
                total_de_doces_recebidos += n_doces;
                //Atualizar a quantidade de doces da família
                atualizar_na_hash_table(nome_da_familia_atual, -n_doces, hash_table);
                //Se a família tiver ficado sem doces, imprimir: "A familia <Nome da Família> ficou sem doces."
                if (max_doces == n_doces && max_doces != 0)
                    printf("A familia %s ficou sem doces.\n", nome_da_familia_atual);
            }
            //Imprimir o resultado. Ex: "Renata Silva recebeu 3 doce(s) das familias."
            if (total_de_doces_recebidos != 0)
                printf("%s %s recebeu %d doce(s) das familias.\n", nome_da_crianca, sobrenome_da_crianca, total_de_doces_recebidos);
            //Se a criança não tiver recebido doces das famílias, a prefeitura dá 10 doces
            else
                printf("%s %s recebeu 10 doces da prefeitura.\n", nome_da_crianca, sobrenome_da_crianca);
        }

        tipo_comando_atual = ler_tipo_comando();
    }

    //Liberar a memória alocada para o vetor da hash_table
    liberar_hash_table(hash_table);

    return 0;
 }
