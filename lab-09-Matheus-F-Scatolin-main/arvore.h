#ifndef ARVORE_H
#define ARVORE_H
#define MAX 202

enum cor {VERMELHO, PRETO};
enum tipo_da_variavel {INT, DOUBLE, CHAR, FLOAT, NAO_ESTA_DEFINIDO};

typedef struct no * p_no;

struct no {
    char simbolo[MAX];
    enum tipo_da_variavel tipo;
    enum cor cor;
    p_no filho_direito;
    p_no filho_esquerdo;
};

/**
 * @brief Esta função cria e retorna uma árvore vazia.
 *
 * @return Um ponteiro para a árvore vazia.
 */
p_no criar_arvore(void);

/**
 * @brief Esta função verifica se um nó da árvore é vermelho.
 *
 * @param no O nó a ser verificado.
 * 
 * @return 1 se o nó for vermelho, 0 caso contrário.
 */
int eh_vermelho(p_no no);

/**
 * @brief Esta função verifica se um nó da árvore é preto.
 *
 * @param no O nó a ser verificado.
 * 
 * @return 1 se o nó for preto, 0 caso contrário.
 */
int eh_preto(p_no no);

/**
 * @brief Esta função realiza uma rotação para a direita em uma árvore binária
 * (operação usada durante a inserção para manter o equilíbrio da árvore).
 *
 * @param raiz A raiz da árvore em que a rotação será realizada.
 * 
 * @return A nova raiz da árvore após a rotação.
 */
p_no rotacionar_para_direita(p_no raiz);

/**
 * @brief Esta função realiza uma rotação para a esquerda em uma árvore binária
 * (operação usada durante a inserção para manter o equilíbrio da árvore).
 *
 * @param raiz A raiz da árvore em que a rotação será realizada.
 * 
 * @return A nova raiz da árvore após a rotação.
 */
p_no rotacionar_para_esquerda(p_no raiz);

/**
 * @brief Esta função realiza a operação de subir a cor vermelha em uma árvore binária,
 * ajustando as cores dos nós filhos para preto, e pintando o pai de vermelho.
 * 
 * @param raiz A raiz da árvore onde a operação será realizada.
 */
void subir_vermelho(p_no raiz);

/**
 * @brief Esta função insere um elemento (símbolo) na árvore, mantendo as propriedade de árvore vermelho-preto.
 *
 * @param raiz A raiz da árvore.
 * @param simbolo O símbolo a ser inserido.
 * @param tipo O tipo do símbolo.
 * 
 * @return A raiz da árvore após a inserção.
 */
p_no inserir_elemento(p_no raiz, char simbolo[], enum tipo_da_variavel tipo);

/**
 * @brief Esta função verifica se um símbolo está definido na árvore e retorna o tipo associado a ele, se definido.
 *
 * @param simbolo O símbolo a ser verificado.
 * @param raiz A raiz da árvore.
 * 
 * @return O tipo do símbolo, se definido, ou NAO_ESTA_DEFINIDO se não estiver definido.
 */
enum tipo_da_variavel verificar_definicao_e_tipo(char simbolo[], p_no raiz);

/**
 * @brief Esta função converte um texto (como "int", "double", etc.) em um tipo de variável correspondente.
 *
 * @param texto O texto a ser convertido.
 * 
 * @return O tipo de variável correspondente.
 * 
 * @example "int" -> INT.
 */
enum tipo_da_variavel texto_em_tipo_da_variavel(char texto[]);

/**
 * @brief Esta função converte um tipo de variável (como INT, DOUBLE, etc.) em um texto correspondente.
 *
 * @param tipo O tipo de variável a ser convertido.
 * 
 * @return O texto correspondente ao tipo de variável.
 * 
 * @example INT -> "int".
 */ 
char* tipo_da_variavel_em_texto(enum tipo_da_variavel tipo);

/**
 * @brief Esta função realiza uma impressão inordenada (ordem esquerda-raiz-direita) da árvore,
 * imprimindo os símbolos e seus tipos.
 *
 * @param raiz A raiz da árvore.
 */
void imprimir_arvore_inordem(p_no raiz);

/**
 * @brief Libera a memória alocada para a árvore de símbolos e seus nós.
 *
 * @param raiz A raiz da árvore a ser liberada.
 */
void liberar_arvore(p_no raiz);

#endif