#include <stdio.h>
#include "grafo.h"

enum tipo_de_comando {ADICIONAR, CONECTAR, DESCONECTAR, TESTAR_CONEXAO, MENOR_CAMINHO, ENCONTRA_CONEXOS, FIM};

/**
 * @brief Lê o tipo de comando a ser executado.
 *
 * @return Tipo de comando lido.
 */
enum tipo_de_comando ler_tipo_de_comando(){
    int comando;
    scanf(" %d", &comando);
    switch (comando){
    case 1:
        return ADICIONAR;
        break;
    case 2:
        return CONECTAR;
        break;
    case 3:
        return DESCONECTAR;
        break;
    case 4:
        return TESTAR_CONEXAO;
        break;
    case 5:
        return MENOR_CAMINHO;
        break;
    case 6:
        return ENCONTRA_CONEXOS;
        break;
    default:
        return FIM;
        break;
    }
}

int main(){
    //Inicializar variáveis
    enum tipo_de_comando comando_atual;
    int vertice_temp_1, vertice_temp_2, acabou = 0;
    //Criar o grafo vazio
    p_grafo grafo = criar_grafo();

    //Iniciar o loop de leitura dos comandos
    comando_atual = ler_tipo_de_comando();
    while (!acabou){
        //Se o comando atual é de adicionar um vértice
        if (comando_atual == ADICIONAR){
            //Ler o vértice a ser adicionado
            scanf(" %d", &vertice_temp_1);
            //Adicionar ele
            adicionar_vertice(vertice_temp_1, grafo);
        }
        //Se o comando atual é de criar uma conexão entre vértices
        else if (comando_atual == CONECTAR){
            //Ler os dois vértices
            scanf(" %d", &vertice_temp_1);
            scanf(" %d", &vertice_temp_2);
            //Conectar eles
            adicionar_aresta(vertice_temp_1, vertice_temp_2, grafo);
        }
        //Se o comando atual é de remover uma conexão entre vértices
        else if (comando_atual == DESCONECTAR){
            //Ler os vértices
            scanf(" %d", &vertice_temp_1);
            scanf(" %d", &vertice_temp_2);
            //Desconectá-los
            remover_aresta(vertice_temp_1, vertice_temp_2, grafo);
        }
        //Se o comando atual é de testar se existe conexão entre dois vértices
        else if (comando_atual == TESTAR_CONEXAO){
            //Ler os vértices
            scanf(" %d", &vertice_temp_1);
            scanf(" %d", &vertice_temp_2);
            //Testar se existe conexao
            if(existe_caminho(grafo, vertice_temp_1, vertice_temp_2))
                printf("Existe conexão entre os nós.\n");
            else
                printf("Não existe conexão entre os nós.\n");
        }
        //Se o comando atual é de encontrar o menor caminho entre dois vértices
        else if (comando_atual == MENOR_CAMINHO){
            //Ler os vértices
            scanf(" %d", &vertice_temp_1);
            scanf(" %d", &vertice_temp_2);
            //Testar se os dois vértices são conexos
            if(!existe_caminho(grafo, vertice_temp_1, vertice_temp_2))
                printf("Não existe conexão entre os nós.\n");
            else
                encontrar_menor_caminho(grafo, vertice_temp_1, vertice_temp_2);
        }
        //Se o comando atual é de encontrar os vértices conexos a cada vértice
        else if (comando_atual == ENCONTRA_CONEXOS){
            //imprimir_conexoes
            imprimir_conexoes(grafo);
        }
        

        comando_atual = ler_tipo_de_comando();
        //Testar se o programa acabou
        if (comando_atual == FIM)
            acabou = 1;
    }
    //Liberar a memória alocada para o grafo
    liberar_grafo(grafo);

    return 0;
}