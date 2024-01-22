#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

p_grafo criar_grafo(void){
    p_grafo grafo = malloc(sizeof(struct grafo));
    grafo->n_vertices = 0;
    grafo->matriz_de_adjacencia = malloc(MAX_VERTICES * sizeof(int *));
    for (int i = 0; i < MAX_VERTICES; i ++)
        grafo->matriz_de_adjacencia[i] = calloc(MAX_VERTICES, sizeof(int));
    return grafo;
}

void liberar_grafo(p_grafo grafo){
    //Liberar a matriz de adjacência
    for (int i = 0; i < MAX_VERTICES; i ++){
        free(grafo->matriz_de_adjacencia[i]);
    }
    free(grafo->matriz_de_adjacencia);
    //Liberar a estrutura em si
    free(grafo);
}

void adicionar_vertice(int n_vertice, p_grafo grafo){
    //Fazer com que o n-ésimo termo da diagonal receba "1", indicando que o vértice n existe
    grafo->matriz_de_adjacencia[n_vertice-1][n_vertice-1] = 1;
    //Aumentar o número de vértices
    grafo->n_vertices += 1;
}

void adicionar_aresta(int n_vertice_1, int n_vertice_2, p_grafo grafo){
    //Fazer com que as duas posições corretas da matriz de adjacência recebam "1"
    grafo->matriz_de_adjacencia[n_vertice_1-1][n_vertice_2-1] = 1;
    grafo->matriz_de_adjacencia[n_vertice_2-1][n_vertice_1-1] = 1;
}

void remover_aresta(int n_vertice_1, int n_vertice_2, p_grafo grafo){
    //Fazer com que as duas posições corretas da matriz recebam 0
    grafo->matriz_de_adjacencia[n_vertice_1-1][n_vertice_2-1] = 0;
    grafo->matriz_de_adjacencia[n_vertice_2-1][n_vertice_1-1] = 0;
    //Note que, se a conexão já não existia, isso não é um problema
}

/**
 * @brief Realiza uma busca em profundidade para verificar se existe um caminho entre vértices.
 *
 * @param grafo Ponteiro para o grafo.
 * @param vert_saida Número do vértice de saída.
 * @param vert_chegada Número do vértice de chegada.
 * @param vert_visitados Vetor que indica os vértices já visitados durante a busca.
 * @return 1 se existe um caminho, 0 caso contrário.
 */
int buscar_recursivamente(p_grafo grafo, int vert_saida, int vert_chegada, int * vert_visitados){
    //Caso base:
    if (vert_chegada == vert_saida)
        return 1;
    //Enquanto não tiver chegado no vértice final, continuar explorando o grafo em profundidade
    vert_visitados[vert_saida-1] = 1;
    //Percorrer a matriz na linha do vértice de saída
    for (int i = 0; i < grafo->n_vertices; i ++)
        //Se existe caminho do vértice de saída ao vértice i+1 e i+1 ainda não foi visitado:
        if (grafo->matriz_de_adjacencia[vert_saida-1][i] && !vert_visitados[i])
            //visita-se recursivamente o vértice i+1
            if (buscar_recursivamente(grafo, i+1, vert_chegada, vert_visitados))
                return 1;
    return 0;
}

int existe_caminho(p_grafo grafo, int vert_saida, int vert_chegada){
    //Criar um vetor com os vértices visitados (adicionar 1 na posição após visitar)
    int vert_visitados[MAX_VERTICES];
    //Zerar todas as posições do vetor
    for (int i = 0; i < MAX_VERTICES; i ++)
        vert_visitados[i] = 0;
    return buscar_recursivamente(grafo, vert_saida, vert_chegada, vert_visitados);
}

/**
 * @brief Imprime recursivamente o caminho entre os vértices de saída e chegada.
 *
 * @param vetor_pais Vetor de pais gerado pela busca em largura.
 * @param vert_saida Número do vértice de saída.
 * @param vert_chegada Número do vértice de chegada.
 */
void imprime_recursivamente(int * vetor_pais, int vert_saida, int vert_chegada){
    //Chamar recursivamente a função a partir do vértice de chegada até o anterior do vértice de saida
    if (vetor_pais[vert_chegada-1] != vert_saida)
        //Chamar a função para o pai do vértice de chegada
        imprime_recursivamente(vetor_pais, vert_saida, vetor_pais[vert_chegada-1]);
    //Por fim imprimir o resultado (o vértice de saída já foi impresso para corrigir a formatação)
    printf(" -> %d", vert_chegada);
}

/**
 * @brief Busca em largura para encontrar o vetor de pais.
 * Nesse vetor, a i-ésima posição contém o vértice que é pai do vértice i+1.
 *
 * @param grafo Ponteiro para o grafo.
 * @param vert_saida Número do vértice de saída.
 * @param vert_chegada Número do vértice de chegada.
 * @return Vetor de pais.
 */
int * busca_em_largura(p_grafo grafo, int vert_saida, int vert_chegada){
    /*1-4/4-3/3-2. Saida = 1/ chegada = 4
    vetor pais = [-1, 3, 4, 1]
    impressão: 1 -> 4 -> 3 -> 2
    */
   //Criar o vetor de pais e de vértices visitados
   int *vetor_pais = malloc(grafo->n_vertices * sizeof(int));
   int *visitados = calloc(grafo->n_vertices, sizeof(int));
   int vert_temp = 0;
    //Setar todas as posições do vetor de pais com -1 inicialmente
    for (int i = 0; i < grafo->n_vertices; i ++)
        vetor_pais[i] = -1;
    
    p_fila fila = criar_fila();
    //Enfileirar o vértice de saída
    enfileirar(fila, vert_saida);
    visitados[vert_saida-1] = 1;
    //Enquanto a fila não estiver vazia e não acharmos o vértice de chegada, continuar buscando
    while(tem_algum_valor(fila) && !visitados[vert_chegada-1]) {
        vert_temp = desenfileirar(fila);
        //Adicionar novos elementos à fila
        for (int i = 0; i < grafo->n_vertices; i ++)
            //Se houver caminho p/ o vértice i+1 e se ele não tiver sido visitado
            if (grafo->matriz_de_adjacencia[vert_temp-1][i] && !visitados[i]){
                visitados[i] = 1;
                vetor_pais[i] = vert_temp;
                enfileirar(fila, i+1);
            }
    }
    //Liberar a memória alocada
    liberar_fila(fila);
    free(visitados);

    return vetor_pais;
}

void encontrar_menor_caminho(p_grafo grafo, int vert_saida, int vert_chegada){
    //Criar um vetor em que a i-ésima posição contém o número do vértice que é pai do vértice i+1
    int * vetor_pais = busca_em_largura(grafo, vert_saida, vert_chegada);

    //Imprimir o menor caminho
    printf("%d", vert_saida);
    imprime_recursivamente(vetor_pais, vert_saida, vert_chegada);
    printf("\n");

    free(vetor_pais);
}

/**
 * @brief Visita recursivamente os vértices para encontrar as componentes conexas.
 *
 * @param grafo Ponteiro para o grafo.
 * @param n_da_componente Número da componente conexa atual.
 * @param componentes_conexas Vetor que armazena as componentes conexas dos vértices.
 * @param vert_atual Número do vértice atual.
 */
void visita_recursiva(p_grafo grafo, int n_da_componente, int * componentes_conexas, int vert_atual){
    //Adicionar o vértice atual à componente atual
    componentes_conexas[vert_atual-1] = n_da_componente;
    //Percorrer a linha na matriz de adjacencia do vértice atual
    for (int i = 0; i < MAX_VERTICES; i ++){
        //Se houver caminho entre o vértice atual e o vértice i+1 e ele ainda não tiver sido visitado:
        if (grafo->matriz_de_adjacencia[vert_atual-1][i] && componentes_conexas[i] == -1){
            //Visitar recursivamente o vértice i+1
            visita_recursiva(grafo, n_da_componente, componentes_conexas, i+1);
            //Note que, dessa forma, adota-se uma busca em profundidade
        }
    }
}

/**
 * @brief Encontra um vetor cuja i-ésima posição indica a componente conexas
 * do grafo em que o vértice i+1 se encontra. Usa-se uma lógica de busca
 * em profundidade.
 *
 * @param grafo Ponteiro para o grafo.
 * @return Vetor que indica a componente conexa de cada vértice.
 */
int * encontrar_componentes_conexas(p_grafo grafo){
    //Criar o vetor
    int * componentes_conexas = malloc(MAX_VERTICES * sizeof(int));
    //Setar todas as posições que ainda devem ser exploradas para -1
    //Setar todas as posições cujos vértices não foram adicionados ao grafo para -2
    for (int i = 0; i < MAX_VERTICES; i ++){
        //Se o vértice está no grafo
        if (grafo->matriz_de_adjacencia[i][i])
            componentes_conexas[i] = -1;
        else
            componentes_conexas[i] = -2;
    }
    //Percorrer cada posição que ainda deve ser explorada
    int n_da_componente = 0;
    for (int j = 0; j < MAX_VERTICES; j ++){
        //Se o vértice j+1 está no grafo e ainda não foi explorado:
        if (componentes_conexas[j] == -1){
            //visitar recursivamente o vértice j+1
            visita_recursiva(grafo, n_da_componente, componentes_conexas, j+1);
            n_da_componente += 1;
        }
    }
    return componentes_conexas;
}

void imprimir_conexoes(p_grafo grafo){
    //Criar um vetor com as componentes conexas do grafo
    //Nesse vetor, se vetor[i] = j, isso indica que o vértice i+1 pertence à j-ésima componente conexa
    int * componentes_conexas = encontrar_componentes_conexas(grafo);

    //Testar se o vértice i está no grafo (se o i-ésimo termo da diagonal é 1)
    for (int i = 0; i < MAX_VERTICES; i ++){
        //se o i-ésimo termo da diagonal é 1:
        if (grafo->matriz_de_adjacencia[i][i]){
            printf("Ponto %d (Pontos diretamente ou indiretamente conectados):", i+1);
            //Fazer um loop passando pelo vetor de componentes conexas, imprimindo todos os termos da mesma componente
            for (int j = 0; j < MAX_VERTICES; j ++) {
                //Se componentes_conexas[j] == componentes_conexas[i] 
                //--> há ligação direta ou indireta entre o vértice i+1 e o j+1
                if (componentes_conexas[i] == componentes_conexas[j])
                    printf(" %d", j+1);
            }
            printf("\n");
        }
    }
    //Liberar a memória alocada
    free(componentes_conexas);
}
