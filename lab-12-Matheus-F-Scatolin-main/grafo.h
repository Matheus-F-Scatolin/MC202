#ifndef GRAFO_H
#define GRAFO_H
#define MAX_VERTICES 20

typedef struct grafo * p_grafo;

struct grafo {
    //Para indicar que o vértice i foi adicionado, matriz_de_adjacência[i][i] recebe 1.
    int ** matriz_de_adjacencia;
    int n_vertices;
};

/**
 * @brief Cria um grafo vazio.
 *
 * @return Ponteiro para o grafo criado.
 */
p_grafo criar_grafo(void);

/**
 * @brief Libera a memória alocada na criação do grafo.
 * 
 * @param grafo Ponteiro para o grafo.
 */
void liberar_grafo(p_grafo grafo);

/**
 * @brief Adiciona um vértice ao grafo.
 *
 * @param n_vertice Número do vértice a ser adicionado.
 * @param grafo Ponteiro para o grafo.
 */
void adicionar_vertice(int n_vertice, p_grafo grafo);

/**
 * @brief Adiciona uma aresta entre dois vértices no grafo.
 *
 * @param n_vertice_1 Número do primeiro vértice.
 * @param n_vertice_2 Número do segundo vértice.
 * @param grafo Ponteiro para o grafo.
 */
void adicionar_aresta(int n_vertice_1, int n_vertice_2, p_grafo grafo);

/**
 * @brief Remove uma aresta entre dois vértices no grafo.
 *
 * @param n_vertice_1 Número do primeiro vértice.
 * @param n_vertice_2 Número do segundo vértice.
 * @param grafo Ponteiro para o grafo.
 */
void remover_aresta(int n_vertice_1, int n_vertice_2, p_grafo grafo);

/**
 * @brief Verifica se existe um caminho entre dois vértices no grafo
 * por meio de uma lógica de busca em profundidade.
 *
 * @param grafo Ponteiro para o grafo.
 * @param vert_saida Número do vértice de saída.
 * @param vert_chegada Número do vértice de chegada.
 * @return 1 se existe um caminho, 0 caso contrário.
 */
int existe_caminho(p_grafo grafo, int vert_saida, int vert_chegada);

/**
 * @brief Encontra o menor caminho entre dois vértices usando uma 
 * lógica de busca em largura e o imprime.
 *
 * @param grafo Ponteiro para o grafo.
 * @param vert_saida Número do vértice de saída (início).
 * @param vert_chegada Número do vértice de chegada (fim).
 */
void encontrar_menor_caminho(p_grafo grafo, int vert_saida, int vert_chegada);

/**
 * @brief Encontra os vértices conectados a cada vértice e imprime as conexões.
 *
 * @param grafo Ponteiro para o grafo.
 */
void imprimir_conexoes(p_grafo grafo);

#endif