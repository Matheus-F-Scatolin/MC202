#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sobrevivente.h"
#include "pedido.h"
#include "fila_prioridades.h"
#define MAX_COMANDO 100
#define MAX_ID 10
enum tipo_de_comando {PEDIDO, ALTERACAO};

/**
 * @brief Extrai os dados de uma alteração (id de quem realizou o pedido
 * e a variação de prioridade) a partir de uma linha de texto no formato
 * "altera <ID> <VALOR>" e armazena eles nas variáveis passadas por referência.
 *
 * @param id_da_alteracao Um ponteiro para uma variável onde o ID da alteração será armazenado.
 * @param variacao_da_prioridade Um ponteiro para uma variável onde a variação da prioridade será armazenada.
 * @param linha_de_texto A linha de texto contendo os dados da alteração.
 */
void encontrar_dados_da_alteracao(int * id_da_alteracao, int * variacao_da_prioridade, char * linha_de_texto){
    //Ex de linha: "altera 1 200000"
    char id[MAX_ID] = "";
    char variacao[MAX_COMANDO] = "";

    //Os caracteres até a posição 6 (inclusive) não nos interessam
    int pos_atual = 7;
    //O ID está entre 7ª posição até o próximo espaço
    for (pos_atual = 7; linha_de_texto[pos_atual] != ' '; pos_atual ++){
        id[pos_atual-7] = linha_de_texto[pos_atual];
    }
    id[pos_atual-7] = '\0';
    (*id_da_alteracao) = atoi(id);

    //Pular o espaço
    pos_atual ++;
    //Começar a ler a variação da prioridade
    int inicio_variacao = pos_atual;
    for (; linha_de_texto[pos_atual] != '\0'; pos_atual ++){
        variacao[pos_atual-inicio_variacao] = linha_de_texto[pos_atual];
    }
    variacao[pos_atual] = '\0';
    (*variacao_da_prioridade) = atoi(variacao);
}


/**
 * @brief Lê um comando da entrada padrão e retorna seu tipo (PEDIDO ou ALTERACAO).
 * O comando é armazenado na variável passada por referência.
 *
 * @param destino_do_texto Um ponteiro para a variável onde o comando lido será armazenado.
 * 
 * @return O tipo de comando (PEDIDO ou ALTERACAO).
 */
enum tipo_de_comando ler_comando(char * destino_do_texto){
    //Exemplo de linha: "novo 3 Banana Pop\n"
    fgets(destino_do_texto, MAX_COMANDO, stdin);

    //Removendo o '\n'
    int pos_final = 0;
    //Percorre a linha até encontrar o \n
    for (pos_final = 0; destino_do_texto[pos_final] != '\n'; pos_final ++);
    //Remove o \n
    destino_do_texto[pos_final] = '\0';

    //Testar se é um pedido ou uma alteração
    char primeira_palavra[MAX_COMANDO];
    sscanf(destino_do_texto, "%s ", primeira_palavra);

    //Se a primeira palavra for "novo", é um pedido
    if (strcmp(primeira_palavra, "novo") == 0)
        return PEDIDO;
    //Se a primeira palavra for "altera", é uma alteração
    return ALTERACAO;
}



int main(void){
    //Se os pedidos acabarem, recebe 1
    int acabaram_os_pedidos = 0;
    int id_da_alteracao = 0, variacao_da_prioridade = 0;
    p_pedido pedido;
    char comando[MAX_COMANDO];
    enum tipo_de_comando tipo_comando;
    int n_pedidos_da_rodada, n_rodada = 1;
    //Ler o número de panelas e o número de sobreviventes
    int n_panelas, n_sobreviventes;
    scanf(" %d %d ", &n_panelas, &n_sobreviventes);

    //Criar uma fila de prioridades que servirá de controle dos pedidos 
    p_fila_de_prioridade fila = criar_fila(n_sobreviventes);

    //Ler e criar um vetor com todos sobreviventes (nome(max 31 caracteres), ID(posição no vetor), número de dias sobrevividos)
    p_sobrevivente * v_sobreviventes = malloc(n_sobreviventes * sizeof(struct sobrevivente));
    for (int i = 0; i < n_sobreviventes; i ++){
        v_sobreviventes[i] = ler_sobrevivente(i);
    }

    //Iniciar um loop para as rodadas
    scanf(" %d ", &n_pedidos_da_rodada);
    //Enquanto o número de pedidos da rodada for diferente de 0 e a fila não estiver vazia:
    while (n_pedidos_da_rodada != 0 || tamanho_da_fila(fila)){
        //Computar cada um dos comandos (diferenciando entre alterações e pedidos)
        for (int i = 0; i < n_pedidos_da_rodada; i++){
            //Ler um comando e identificar seu tipo (alteração ou pedido)
            tipo_comando = ler_comando(comando);

            //Formato pedido: novo <ID> <PRATO> (tamanho max do prato: 25 caracteres)
            if (tipo_comando == PEDIDO){
                pedido = criar_pedido(comando, v_sobreviventes);
                //colocar o pedido na fila
                inserir_novo_pedido(pedido, fila);
            }
            //Formato alterações: altera <ID> <VALOR>
            else if (tipo_comando == ALTERACAO){
                encontrar_dados_da_alteracao(&id_da_alteracao, &variacao_da_prioridade, comando);
                alterar_prioridade(fila, v_sobreviventes[id_da_alteracao], variacao_da_prioridade);
            }
        }
        
        //Entregar os pedidos da rodada e imprimir o resultado(<NOME> <SOBRENOME> <PRATO> <PRIORIDADE ATUAL>)
        printf("---- rodada %d ----\n", n_rodada);
        for (int i = 0; i < n_panelas; i++){
            //Testar se tem algum pedido na fila de prioridades, e prepará-lo
            if (tamanho_da_fila(fila)){
                pedido = extrair_pedido(fila);
                //Imprimir o pedido
                printf("%s %s %d\n", quem_pediu(v_sobreviventes , pedido), nome_prato(pedido), descobrir_prioridade(pedido));
                //Liberar a memória alocada
                liberar_pedido(pedido, v_sobreviventes);
            }
            else
                break;
        }

        //Ver se os pedidos acabaram
        if (n_pedidos_da_rodada == 0)
            acabaram_os_pedidos = 1;

        //Ler o número de pedidos da próxima rodada se os pedidos não tiverem acabado
        if (!acabaram_os_pedidos)
            scanf(" %d ", &n_pedidos_da_rodada);
        //Aumentar o número da rodada
        n_rodada += 1;
    }

    //Liberar a memoria alocada para os sobreviventes e para a fila de prioridades
    liberar_fila(fila);
    liberar_sobreviventes(v_sobreviventes, n_sobreviventes);
    free(v_sobreviventes);

    return 0;
}

