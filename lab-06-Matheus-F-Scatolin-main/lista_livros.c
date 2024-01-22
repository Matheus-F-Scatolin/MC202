#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_livros.h"

void liberar_lista(lista_livros* lista){
    if (lista != NULL){
        liberar_lista(lista->proximo);
        free(lista->livro);
        free(lista);
    }
}

lista_livros * criar_lista(void){
    return NULL;
}

char * ler_livro(void){
    char *livro = malloc(56*sizeof(char));
    fgets(livro, 56*sizeof(char), stdin);

    //Remover o espaço no começo da palavra e o \n no final
    if (livro[0] == ' '){
        for (int c=0; c<55; c++){
            livro[c] = livro[c+1];
            if (livro[c] == '\n')
                livro[c] = '\0';
            if (livro[c] == '\0')
                break;
        }
    }
    return livro;
}

lista_livros * remover_elemento(lista_livros* lista, int * posicao){
    //Ler livro a ser deletado
    char *nome;
    nome = ler_livro();

    //Percorrer a lista até encontrar o livro certo
    int contador = 0;
    lista_livros * anterior = lista;
    lista_livros * atual;
    if (anterior->proximo!=NULL && strcmp(anterior->livro, nome) != 0){
        atual = anterior->proximo;
        contador++;
    }
    else
        atual = anterior;
    while (atual->proximo!=NULL && strcmp(atual->livro, nome) != 0){
        if (strcmp(atual->livro, nome) == 0)
            break;
        anterior = atual;
        atual = anterior->proximo;
        contador ++;
    }
    free(nome);
    //Remover o elemento
    if (contador != 0)
        anterior->proximo = atual->proximo;
    else
        lista = atual->proximo;
    free(atual->livro);
    free(atual);

    //Verificar a posição que o proximo livro deverá ser adicionado
    if (*posicao > contador){
        *posicao -= 1;
    }
    return lista;
}



lista_livros * adicionar_elemento(lista_livros* lista, int posicao){
    lista_livros *novo = malloc(sizeof(lista_livros));
    char * livro = ler_livro();
    novo->livro = livro;
    if (lista == NULL||posicao==0){
        novo->proximo = lista;
        return novo;
    }
    else{
        lista_livros *atual = lista;
        for (int c = 0; c<posicao-1; atual = atual->proximo, c++);
        novo->proximo = atual->proximo;
        atual->proximo = novo;
        return lista;
    }
}

int encontrar_final(lista_livros * lista){
    int posicao = 0;
    if (lista == NULL)
        return 0;
    while (lista->proximo!= NULL){
        posicao ++;
        lista = lista->proximo;
    }
    return posicao+1;
}

void imprime_lista(lista_livros* lista){
    lista_livros * atual = lista;
    if (lista)
        printf("%s", atual->livro);
    while (atual->proximo!=NULL){
        atual = atual->proximo;
        printf(", %s", atual->livro);
    }
    printf("\n");
}

int ler_comando(void){
    char comando[10];
    int teste_eof;
    teste_eof = scanf(" %s", comando);
    if (teste_eof == EOF)
        return 0;
    else if (strcmp(comando, "inicio") == 0)
        return 2;
    else if (strcmp(comando, "final") == 0)
        return 3;
    else if (strcmp(comando, "remover") == 0)
        return 4;
    else if (strcmp(comando, "imprimir") == 0)
        return 5;
    return 1;
}

lista_livros * executar_comando(lista_livros * lista, int comando, int * posicao){
    if (comando == 2){
        *posicao = 0;
        return lista;
    }
    else if (comando == 3){
        *posicao = encontrar_final(lista);
        return lista;
    }
    else if (comando == 4){
        lista = remover_elemento(lista, posicao);
        return lista;
    }
    else if (comando == 5){
        imprime_lista(lista);
        return lista;
    }
    else{ //comando = 1
        lista = adicionar_elemento(lista, *posicao);
        *posicao+=1;
        return lista;
    }
}