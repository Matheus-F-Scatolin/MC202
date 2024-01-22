#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "no.h"
#define N_OPERADORES 10
#define N_NUMEROS 11

const char operadores[N_OPERADORES] = "{}<>&|=!";
const char numeros[N_NUMEROS] = "0123456789";

//Retorna 1 se o caractere for um número ou uma variável. Retorna 0 no caso contrário.
int eh_operador(char caractere){
    for(int c=0; operadores[c]!='\0';c++)
        if (operadores[c] == caractere)
            return 1;
    return 0;
}

int eh_numero(char caractere){
    for(int c=0; numeros[c]!='\0';c++)
        if (numeros[c] == caractere)
            return 1;
    return 0;
}

void liberar_arvore(p_arvore arvore){
    if (arvore == NULL)
        return;
    liberar_arvore(arvore->filho_direito);
    liberar_arvore(arvore->filho_esquerdo);
    free(arvore);
}

p_arvore criar_arvore(char caractere){
    p_arvore arvore = malloc(sizeof(struct arvore));
    arvore->filho_direito = NULL;
    arvore->filho_esquerdo = NULL;
    arvore->dado = caractere;
    return arvore;
}

void adicionar_filhos(p_arvore arvore_resultante, p_arvore filho_esq, p_arvore filho_dir){
    arvore_resultante->filho_direito = filho_dir;
    arvore_resultante->filho_esquerdo = filho_esq;
}

void imprime_arvore_inordem(p_arvore arvore, p_arvore no_pai){
    if (arvore == NULL)
        return;

    // Adiciona parênteses se a arvore atual for o filho esquerdo de um operador
    if ((no_pai != NULL) && (arvore == no_pai->filho_esquerdo) && (eh_operador(no_pai->dado)))
        printf("(");

    imprime_arvore_inordem(arvore->filho_esquerdo, arvore);

    if (eh_operador(arvore->dado)){
        printf(" ");
        printf("%c", arvore->dado);
        printf(" ");
    }
    else
        printf("%c", arvore->dado);

    imprime_arvore_inordem(arvore->filho_direito, arvore);

    // Adiciona parênteses de fechamento se a arvore atual for o filho direito de um operador
    if (((no_pai != NULL) && arvore == no_pai->filho_direito) && (eh_operador(no_pai->dado)))
        printf(")");
}

//Libera os filhos da arvore, seta os ponteiros para NULL e muda o valor do nó
p_arvore liberar_filhos_e_setar_valor(p_arvore arvore, char novo_valor){
    liberar_arvore(arvore->filho_esquerdo);
    liberar_arvore(arvore->filho_direito);
    arvore->filho_direito = NULL;
    arvore->filho_esquerdo = NULL;
    arvore->dado = novo_valor;
    return arvore;
}

/*Dado um nó da arvore com um operando de desigualdade matemática, a função tenta otimizar a operação
e retorna a arvore resultante após a otimização*/
p_arvore otimiza_expressao_relacional(p_arvore arvore){
    if (arvore->dado == '>'){
        //Se a expressão for do tipo x>9  ou 0>x-> Falso
        if ((arvore->filho_direito->dado == '9')| (arvore->filho_esquerdo->dado == '0'))
            return liberar_filhos_e_setar_valor(arvore, 'F');
        
        //Se a expressão for do tipo x>x -> Falso
        if (arvore->filho_direito->dado == arvore->filho_esquerdo->dado)
            return liberar_filhos_e_setar_valor(arvore, 'F');
        
        //Se a expressão for do tipo 3>5 -> executar ela matematicamente
        if (eh_numero(arvore->filho_esquerdo->dado) && eh_numero(arvore->filho_direito->dado)){
            int expressao = arvore->filho_esquerdo->dado > arvore->filho_direito->dado;
            return liberar_filhos_e_setar_valor(arvore, expressao ? 'T' : 'F');
        }
    }
    else if (arvore->dado == '<'){
        //Se a expressão for do tipo 9<x ou x<0 -> Falso
        if ((arvore->filho_esquerdo->dado == '9')|(arvore->filho_direito->dado == '0'))
            return liberar_filhos_e_setar_valor(arvore, 'F');
        
        //Se a expressão for do tipo x<x -> Falso
        if (arvore->filho_direito->dado == arvore->filho_esquerdo->dado)
            return liberar_filhos_e_setar_valor(arvore, 'F');
        
        //Se a expressão for do tipo 3<5 (numero<numero)-> executar ela matematicamente
        if (eh_numero(arvore->filho_esquerdo->dado) && eh_numero(arvore->filho_direito->dado)){
            int expressao = arvore->filho_esquerdo->dado < arvore->filho_direito->dado;
            return liberar_filhos_e_setar_valor(arvore, expressao ? 'T' : 'F');
        }
    }
    else if (arvore->dado == '{'){
        //Se a expressão for do tipo x{9-> True
        if ((arvore->filho_direito->dado == '9'))
            return liberar_filhos_e_setar_valor(arvore, 'T');
        
        //Se a expressão for do tipo 0{x-> True
        if ((arvore->filho_esquerdo->dado == '0'))
            return liberar_filhos_e_setar_valor(arvore, 'T');
        
        //Se a expressão for do tipo x{x -> True
        if (arvore->filho_direito->dado == arvore->filho_esquerdo->dado)
            return liberar_filhos_e_setar_valor(arvore, 'T');
        
        //Se a expressão for do tipo 3{5 (numero{numero)-> executar ela matematicamente
        if (eh_numero(arvore->filho_direito->dado) && eh_numero(arvore->filho_esquerdo->dado)){
            int expressao = arvore->filho_esquerdo->dado <= arvore->filho_direito->dado;
            return liberar_filhos_e_setar_valor(arvore, expressao ? 'T' : 'F');
        }
    }
    else if (arvore->dado == '}'){
        //Se a expressão for do tipo 9}x-> True
        if ((arvore->filho_esquerdo->dado == '9'))
            return liberar_filhos_e_setar_valor(arvore, 'T');

        //Se a expressão for do tipo x}0-> True
        if ((arvore->filho_direito->dado == '0'))
            return liberar_filhos_e_setar_valor(arvore, 'T');
        
        //Se a expressão for do tipo x}x -> True
        if (arvore->filho_direito->dado == arvore->filho_esquerdo->dado)
            return liberar_filhos_e_setar_valor(arvore, 'T');
        
        //Se a expressão for do tipo 3}5 (numero}numero)-> executar ela matematicamente
        if (eh_numero(arvore->filho_direito->dado) && eh_numero(arvore->filho_esquerdo->dado)){
            int expressao = arvore->filho_esquerdo->dado >= arvore->filho_direito->dado;
            return liberar_filhos_e_setar_valor(arvore, expressao ? 'T' : 'F');
        }    
    }
    //Se nenhuma das condições for satisteita, devolve-se a árvore original
    return arvore;
}

p_arvore otimiza_comparacao(p_arvore arvore){
    if (arvore->dado == '='){
        //Se a expressão for do tipo x=x ->True
        if ((arvore->filho_esquerdo->dado == arvore->filho_direito->dado)&&(!eh_operador(arvore->filho_esquerdo->dado)))
            return liberar_filhos_e_setar_valor(arvore, 'T');
        //Se a expressão for do tipo 3=5 (numero=numero)-> executar ela matematicamente
        if (eh_numero(arvore->filho_direito->dado) && eh_numero(arvore->filho_esquerdo->dado)){
            int expressao = (arvore->filho_esquerdo->dado == arvore->filho_direito->dado);
            return liberar_filhos_e_setar_valor(arvore, expressao ? 'T' : 'F');
            }
    }
    else if (arvore->dado == '!'){
        //Se a expressão for do tipo x!x -> Falso
        if ((arvore->filho_esquerdo->dado == arvore->filho_direito->dado)&&(!eh_operador(arvore->filho_esquerdo->dado)))
            return liberar_filhos_e_setar_valor(arvore, 'F');
        //Se a expressão for do tipo 3=5 (numero=numero)-> executar ela matematicamente
        if (eh_numero(arvore->filho_direito->dado) && eh_numero(arvore->filho_esquerdo->dado)){
            int expressao = (arvore->filho_esquerdo->dado != arvore->filho_direito->dado);
            return liberar_filhos_e_setar_valor(arvore, expressao ? 'T' : 'F');
        }
    }
    //Se nenhuma das condições for satisteita, devolve-se a árvore original
    return arvore;
}

p_arvore otimiza_operador_logico(p_arvore arvore){
    if (arvore->dado == '&'){
        //Se a expressão for do tipo F|x ou x|F-> Falso
        if (arvore->filho_esquerdo->dado == 'F' || arvore->filho_direito->dado == 'F')
            return liberar_filhos_e_setar_valor(arvore, 'F');
        
    }
    if (arvore->dado == '|'){
        //Se a expressão for do tipo T|x ou x|T-> True
        if (arvore->filho_esquerdo->dado == 'T' || arvore->filho_direito->dado == 'T')
            return liberar_filhos_e_setar_valor(arvore, 'T');
        
    }
    //Se nenhuma das condições for satisteita, devolve-se a árvore original
    return arvore;
}

/*Dado um nó da arvore com um operando e dois operadores (os filhos), a função tenta otimizar a operação
e retorna a arvore resultante após a otimização*/
p_arvore otimizar_operacao(p_arvore arvore){
    switch (arvore->dado)
    {
    case '>':
    case '<':
    case '}':
    case '{':
        return otimiza_expressao_relacional(arvore);
        break;
    case '&':
    case '|':
        return otimiza_operador_logico(arvore);
    case '=':
    case '!':
        return otimiza_comparacao(arvore);
    default:
        return arvore;
        break;
    }
}

p_arvore simplifica_arvore(p_arvore arvore){
    if (arvore == NULL)
        return arvore;

    arvore->filho_esquerdo = simplifica_arvore(arvore->filho_esquerdo);
    arvore->filho_direito = simplifica_arvore(arvore->filho_direito);
    if (eh_operador(arvore->dado)){
        return otimizar_operacao(arvore);
    }
    else
        return arvore;
}
