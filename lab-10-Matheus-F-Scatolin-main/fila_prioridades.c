#include "fila_prioridades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAI(i) ((i-1)/2)
#define FILHO_ESQ(i) ((i*2+1))
#define FILHO_DIR(i) ((i*2+2))

p_fila_de_prioridade criar_fila(int n_sobreviventes){
    p_fila_de_prioridade fila = malloc(sizeof(struct fila_de_prioridade));
    fila->tamanho = 0;
    fila->vetor = malloc(n_sobreviventes * sizeof(struct pedido));
    return fila;
}

void troca(p_pedido * pedido_1, p_pedido * pedido_2){
    //Fazer a troca
    p_pedido pedido_temp = *pedido_1;
    *pedido_1 = *pedido_2;
    *pedido_2 = pedido_temp;
    //Atualizar as posiçoes dos pedidos
    int pos_temp = (*pedido_1)->pos_na_f_prio;
    (*pedido_1)->pos_na_f_prio = (*pedido_2)->pos_na_f_prio;
    (*pedido_2)->pos_na_f_prio = pos_temp;
}

int tamanho_da_fila(p_fila_de_prioridade fila){
    return fila->tamanho;
}


int encontrar_maior_filho(p_fila_de_prioridade fila, int posicao){
    //Testar se há filhos
    if (FILHO_ESQ(posicao) < fila->tamanho){
        //Testar se o filho direito existe e se ele é maior que o esquerdo
        if (FILHO_DIR(posicao) < fila->tamanho){
            //Se sim, retornar a pposição do filho direito
            if (fila->vetor[FILHO_DIR(posicao)]->prioridade > fila->vetor[FILHO_ESQ(posicao)]->prioridade){
                return FILHO_DIR(posicao);
            }
        //Se não, retornar a posição do filho esquerdo
        }
        return FILHO_ESQ(posicao);
    }
    //Se não houver filhos, retornar -1
    return -1;
}

void desce_no_heap(p_fila_de_prioridade fila, int posicao){
    //Encontrar o maior filho do nó atual
    int pos_maior_filho = encontrar_maior_filho(fila, posicao);
    //Se a posição atual tiver um filho
    if (pos_maior_filho != -1){
        //Se o filho tiver prioridade maior que a posição atual
        if (fila->vetor[pos_maior_filho]->prioridade > fila->vetor[posicao]->prioridade){
            //Trocar a posição atual com o seu maior filho
            troca(&fila->vetor[posicao], &fila->vetor[pos_maior_filho]);
            desce_no_heap(fila, pos_maior_filho);
        }
    }
}

p_pedido extrair_pedido(p_fila_de_prioridade fila){
    //Definir o pedido a ser extraído
    p_pedido pedido = fila->vetor[0];
    //Trocar ele de lugar com o último
    troca(&fila->vetor[0], &fila->vetor[fila->tamanho-1]);
    //Reduzir o tamanho usado do vetor
    fila->tamanho -= 1;
    //Descer o último (que agora é o primeiro) no heap
    desce_no_heap(fila, 0);
    //Retornar o pedido
    return pedido;
}

void sobe_no_heap(p_fila_de_prioridade fila, int pos_insercao){
    //Testar se o heap não está vazio e se o filho não é maior que o pai
    if (pos_insercao > 0 && fila->vetor[pos_insercao]->prioridade > fila->vetor[PAI(pos_insercao)]->prioridade){
        //Se o filho for maior que o pai, trocar eles
        troca(&fila->vetor[pos_insercao], &fila->vetor[PAI(pos_insercao)]);
        //E chamar recursivamente a função para a posição do pai
        sobe_no_heap(fila, PAI(pos_insercao));
    }
    return;
}


void inserir_novo_pedido(p_pedido novo_pedido, p_fila_de_prioridade fila){
    //Inserir o pedido no final do vetor e atualizar sua posição
    fila->vetor[fila->tamanho] = novo_pedido;
    novo_pedido->pos_na_f_prio = fila->tamanho;
    //E subir ele até a posião adequada
    sobe_no_heap(fila, fila->tamanho);
    //Aumentar o tamanho usado do vetor
    fila->tamanho ++;
}

void alterar_prioridade(p_fila_de_prioridade fila, p_sobrevivente sob_que_pediu, int variacao_da_prioridade){
    //Encontrar a posição original desse pedido na fila de prioridades
    int posicao = sob_que_pediu->pedido_atual->pos_na_f_prio;
    //Alterar a prioridade
    sob_que_pediu->pedido_atual->prioridade += variacao_da_prioridade;
    //Arrumar a fila de prioridades após essa alteração
    if (variacao_da_prioridade > 0){
        sobe_no_heap(fila, posicao);
    }
    else{
        desce_no_heap(fila, posicao);
    }
}

void liberar_fila(p_fila_de_prioridade fila){
    free(fila->vetor);
    free(fila);
}
