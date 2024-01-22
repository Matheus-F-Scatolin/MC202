#ifndef LISTA_LIVROS_H
#define LISTA_LIVROS_H

/*
Estrutura que representa um elemento de uma lista de livros.
 */
typedef struct _lista_livros{
    char * livro;
    struct _lista_livros * proximo;
} lista_livros;

/**
 * @brief Cria uma nova lista de livros vazia.
 *
 * @return Ponteiro para a lista de livros vazia.
 */
lista_livros * criar_lista(void);

/**
 * @brief Lê o nome de um livro.
 *
 * @return Ponteiro para uma string contendo o nome do livro lido.
 */
char * ler_livro(void);

/**
 * @brief Adiciona um novo livro à lista de livros em uma posição específica.
 *
 * @param lista Ponteiro para a lista de livros.
 * @param posicao A posição em que o livro deve ser adicionado (0 para o início).
 * @return Ponteiro para a lista atualizada.
 */
lista_livros * adicionar_elemento(lista_livros* lista, int posicao);

/**
 * @brief Remove um livro da lista de livros em uma posição específica.
 *
 * @param lista Ponteiro para a lista de livros.
 * @param posicao Ponteiro para a posição em que o livro deve ser removido.
 * @return Ponteiro para a lista atualizada.
 */
lista_livros * remover_elemento(lista_livros* lista, int * posicao);

/**
 * @brief Encontra a posição do último livro na lista de livros.
 *
 * @param lista Ponteiro para a lista de livros.
 * @return A posição depois do último livro na lista.
 */
int encontrar_final(lista_livros * lista);

/**
 * @brief Lê um comando e retorna seu código.
 *
 * @return O código do comando lido:
 * 0 - final do arquivo (EOF);
 * 1 - adicionar;
 * 2 - inicio;
 * 3 - final;
 * 4 - remover;
 * 5 - imprimir.
 */
int ler_comando(void);

/**
 * @brief Executa um comando específico na lista de livros.
 *
 * @param lista Ponteiro para a lista de livros.
 * @param comando O código do comando a ser executado.
 * @param posicao Ponteiro para a posição do próximo livro a ser adicionado.
 * @return Ponteiro para a lista atualizada após a execução do comando.
 */
lista_livros* executar_comando(lista_livros *lista, int comando, int * posicao);

/**
 * @brief Imprime a lista de livros na saída padrão (stdout).
 *
 * @param lista Ponteiro para a lista de livros a ser impressa.
 */
void imprime_lista(lista_livros* lista);

/**
 * @brief Libera a lista.
 * 
 * @param lista Ponteiro para a lista de livros.
*/
void liberar_lista(lista_livros* lista);

#endif