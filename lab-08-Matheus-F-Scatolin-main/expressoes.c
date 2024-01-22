#include <stdio.h>
#include "pilha.h"
#include "arvore.h"

int main(void){
    int n_expressoes;
    p_arvore filho_esq=NULL, filho_dir=NULL, arvore_resultante=NULL;
    p_pilha pilha = criar_pilha();
    p_arvore arvore=NULL, arvore_final=NULL;
    scanf(" %d", &n_expressoes);
    for(int c = 0; c < n_expressoes; c++){
        char caractere;
        scanf(" %c", &caractere);
        while (caractere!='\n'){
            if (!eh_operador(caractere)){
                arvore = criar_arvore(caractere);
                empilhar(pilha, arvore);
            }
            else{
                //Desempilhar o nó da direita
                filho_dir = desempilhar(pilha);
                //Desempilhar o nó da esquerda
                filho_esq = desempilhar(pilha);
                arvore_resultante = criar_arvore(caractere);
                adicionar_filhos(arvore_resultante, filho_esq, filho_dir);
                empilhar(pilha, arvore_resultante);
            }

            scanf("%c", &caractere);
        }

        arvore_final = desempilhar(pilha);

        imprime_arvore_inordem(arvore_final, NULL);
        printf("\n");

        arvore_final = simplifica_arvore(arvore_final);
        imprime_arvore_inordem(arvore_final, NULL);
        printf("\n");
        printf("\n");
        liberar_arvore(arvore_final);
        arvore_final = NULL;
    }

    liberar_pilha(pilha);

    return 0;
}
