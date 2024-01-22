#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore * p_arvore;

/**
 * @brief Estrutura para representar uma árvore.
 */
struct arvore {
    char dado;
    p_arvore filho_esquerdo;
    p_arvore filho_direito;
};

/**
 * @brief Verifica se o caractere é um operador.
 *
 * @param caractere O caractere a ser verificado.
 * @return 1 se for um operador, 0 caso contrário.
 */
int eh_operador(char caractere);

/**
 * @brief Verifica se o caractere é um número.
 *
 * @param caractere O caractere a ser verificado.
 * @return 1 se for um número, 0 caso contrário.
 */
int eh_numero(char caractere);

/**
 * @brief Libera a memória ocupada pela árvore e seus nós.
 *
 * @param arvore Ponteiro para a árvore a ser liberada.
 */
void liberar_arvore(p_arvore arvore);

/**
 * @brief Cria uma nova árvore com o caractere especificado.
 *
 * @param caractere O caractere a ser armazenado no nó da árvore.
 * @return Ponteiro para a nova árvore criada.
 */
p_arvore criar_arvore(char caractere);

/**
 * @brief Adiciona os filhos especificados a uma árvore.
 *
 * @param arvore_resultante Ponteiro para a árvore resultante.
 * @param filho_esq Ponteiro para o filho esquerdo a ser adicionado.
 * @param filho_dir Ponteiro para o filho direito a ser adicionado.
 */
void adicionar_filhos(p_arvore arvore_resultante, p_arvore filho_esq, p_arvore filho_dir);

/**
 * @brief Imprime a árvore no formato inordem.
 *
 * @param arvore Ponteiro para a árvore a ser impressa.
 * @param no_pai Ponteiro para o nó pai (usado para adicionar parênteses quando necessário).
 */
void imprime_arvore_inordem(p_arvore arvore, p_arvore no_pai);

/**
 * @brief Esta função otimiza uma árvore de expressão relacional, reduzindo-a a um valor lógico simples (verdadeiro ou falso)
 * quando possível. Por exemplo, ela pode simplificar expressões como "x > 9" para "F" (falso) ou "3 < 5" para "T" (verdadeiro).
 *
 * @param arvore Ponteiro para a árvore contendo a expressão relacional.
 * @return Ponteiro para a árvore otimizada.
 */
p_arvore otimiza_expressao_relacional(p_arvore arvore);

/**
 * @brief Esta função otimiza a árvore de operação de comparação, reduzindo-a a um valor lógico simples (verdadeiro ou falso)
 * quando possível. Por exemplo, ela pode simplificar expressões como "x = x" para "T" (verdadeiro) ou "3 ! 3" para "F" (falso).
 *
 * @param arvore Ponteiro para a árvore contendo a operação de comparação.
 * @return Ponteiro para a árvore otimizada.
 */
p_arvore otimiza_comparacao(p_arvore arvore);

/**
 * @brief Esta função otimiza a árvore de operador lógico, reduzindo-a a um valor lógico simples (verdadeiro ou falso)
 * quando possível. Por exemplo, ela pode simplificar expressões como "F & x" para "F" (falso) ou "T | x" para "T" (verdadeiro).
 *
 * @param arvore Ponteiro para a árvore contendo o operador lógico.
 * @return Ponteiro para a árvore otimizada.
 */
p_arvore otimiza_operador_logico(p_arvore arvore);

/**
 * @brief Esta função verifica o tipo de operação contida na árvore e chama a função de otimização correspondente,
 * como otimiza_expressao_relacional(), otimiza_comparacao() ou otimiza_operador_logico(), dependendo do operador encontrado.
 *
 * @param arvore Ponteiro para a árvore contendo a operação.
 * @return Ponteiro para a árvore otimizada.
 */
p_arvore otimizar_operacao(p_arvore arvore);

/**
 * @brief Simplifica uma árvore de expressão.
 *
 * Esta função simplifica uma árvore de expressão, aplicando otimizações específicas, como redução de expressões lógicas
 * e aritméticas simples. Ela percorre a árvore e chama as funções de otimização adequadas para cada tipo de nó.
 *
 * @param arvore Ponteiro para a árvore de expressão a ser simplificada.
 * @return Ponteiro para a árvore simplificada.
 */
p_arvore simplifica_arvore(p_arvore arvore);

#endif