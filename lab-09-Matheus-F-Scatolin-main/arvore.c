#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

p_no criar_arvore(void){
    return NULL;
}

int eh_vermelho(p_no no){
    if (no == NULL)
        return 0;
    return (no->cor == VERMELHO);
}

int eh_preto(p_no no){
    if (no == NULL)
        return 1;
    return (no->cor == PRETO);
}

p_no rotacionar_para_direita(p_no raiz){
    p_no nova_raiz;
    nova_raiz = raiz->filho_esquerdo;
    raiz->filho_esquerdo = nova_raiz->filho_direito;
    nova_raiz->filho_direito = raiz;
    nova_raiz->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return nova_raiz;
}

p_no rotacionar_para_esquerda(p_no raiz){
    p_no nova_raiz;
    nova_raiz = raiz->filho_direito;
    raiz->filho_direito = nova_raiz->filho_esquerdo;
    nova_raiz->filho_esquerdo = raiz;
    nova_raiz->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return nova_raiz;
}

void subir_vermelho(p_no raiz){
    raiz->filho_direito->cor = PRETO;
    raiz->filho_esquerdo->cor = PRETO;
    raiz->cor = VERMELHO;
}

/**
 * @brief Esta função é chamada recursivamente para inserir um novo nó na árvore de símbolos.
 * Ela insere o nó de acordo com a ordem lexicográfica dos símbolos.
 *
 * @param raiz A raiz da árvore onde o nó será inserido.
 * @param simbolo O símbolo a ser inserido.
 * @param tipo O tipo associado ao símbolo a ser inserido.
 * 
 * @return A raiz da árvore atualizada após a inserção.
 */
p_no auxiliar_recursivo_insercao(p_no raiz, char simbolo[], enum tipo_da_variavel tipo){
    //Se a raiz atual for NULL, encontramos o local de inserção
    if (raiz == NULL){
        p_no novo_no = malloc(sizeof(struct no));
        novo_no->cor = VERMELHO;
        novo_no->filho_direito = NULL;
        novo_no->filho_esquerdo = NULL;
        strcpy(novo_no->simbolo, simbolo);
        novo_no->tipo = tipo;
        return novo_no;
    }
    else{
        //Verificar se a palavra do novo nó, em ordem alfabética, vem antes da palavra atual
        //(Se strcmp retornar um valor negativo, significa que a primeira string vem antes.)
        if (strcmp(simbolo, raiz->simbolo)<0){
            raiz->filho_esquerdo = auxiliar_recursivo_insercao(raiz->filho_esquerdo, simbolo, tipo);
        }
        //Se a palavra, em ordem alfabética, vier depois da palavra atual
        else{
            raiz->filho_direito = auxiliar_recursivo_insercao(raiz->filho_direito, simbolo, tipo);
        }
    }
    //CORRIGINDO A ÁRVORE
    if (eh_vermelho(raiz->filho_direito) && eh_preto(raiz->filho_esquerdo))
        raiz = rotacionar_para_esquerda(raiz);

    if (eh_vermelho(raiz->filho_esquerdo) && eh_vermelho(raiz->filho_esquerdo->filho_esquerdo))
        raiz = rotacionar_para_direita(raiz);

    if (eh_vermelho(raiz->filho_esquerdo) && eh_vermelho(raiz->filho_direito))
        subir_vermelho(raiz);

    return raiz;
}


p_no inserir_elemento(p_no raiz, char simbolo[], enum tipo_da_variavel tipo){
    raiz = auxiliar_recursivo_insercao(raiz, simbolo, tipo);
    raiz->cor = PRETO;
    return raiz;
}

enum tipo_da_variavel verificar_definicao_e_tipo(char simbolo[], p_no raiz){
    if (raiz == NULL)
        return NAO_ESTA_DEFINIDO;
    if (strcmp(raiz->simbolo, simbolo) == 0)
        return raiz->tipo;
    //Chamar recursivamente a função para os nós filhos
    if (strcmp(simbolo, raiz->simbolo) < 0){
        //Se o simbolo buscado vier antes da palavra atual (lexicograficamente), buscar para a esquerda
        return verificar_definicao_e_tipo(simbolo, raiz->filho_esquerdo);
    }
    //Caso contrário, buscar para a direita
    return verificar_definicao_e_tipo(simbolo, raiz->filho_direito);
}

//Transforma texto em uma variavel do tipo "tipo_de_variavel". Ex: "int" -> INT.
enum tipo_da_variavel texto_em_tipo_da_variavel(char texto[]){
    if (strcmp(texto, "int") == 0)
        return INT;
    if (strcmp(texto, "double") == 0)
        return DOUBLE;
    if (strcmp(texto, "char") == 0)
        return CHAR;
    if (strcmp(texto, "float") == 0) 
        return FLOAT;

    return NAO_ESTA_DEFINIDO;
}

//Transforma uma variavel do tipo "tipo_de_variavel" em texto. Ex: INT -> "int".
char* tipo_da_variavel_em_texto(enum tipo_da_variavel tipo) {
    switch (tipo) {
        case INT:
            return "int";
        case DOUBLE:
            return "double";
        case CHAR:
            return "char";
        case FLOAT:
            return "float";
        default:
            return "ERRO";
    }
}

void imprimir_arvore_inordem(p_no raiz){
    if (raiz == NULL)
        return;
    
    imprimir_arvore_inordem(raiz->filho_esquerdo);
    //Formato da impressão: "Addison_Hoover int"
    printf("%s %s\n", raiz->simbolo, tipo_da_variavel_em_texto(raiz->tipo));
    imprimir_arvore_inordem(raiz->filho_direito);
}

void liberar_arvore(p_no raiz){
    if (raiz == NULL)
        return;
    liberar_arvore(raiz->filho_esquerdo);
    liberar_arvore(raiz->filho_direito);
    free(raiz);
}