#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batmemoria.h"
/*
OBSERVAÇÃO: Toda a documentação das funções e de
seus parâmetros está no arquivo batmemoria.h.
*/



batmemoria * criar_batmemoria(){
    batmemoria *bat_memoria;
    bat_memoria = calloc(1,sizeof(batmemoria));
    (bat_memoria)->espaco_total = 8;
    (bat_memoria)->espaço_usado = 0;
    (bat_memoria)->registro_das_posicoes = calloc(8,sizeof(int));
    (bat_memoria)->memoria = calloc(8,sizeof(int));
    return bat_memoria;
}

int ler_comando(void){
    char comando[12];
    scanf(" %s", comando);
    if (strcmp(comando, "bat-alloc") == 0)
        return 1;
    else if (strcmp(comando, "bat-free") == 0)
        return 2;
    else if (strcmp(comando, "bat-print") == 0)
        return 3;
    else if (strcmp(comando, "bat-uso") == 0)
        return 4;
    
    return -1;
}

void dobrar_memoria(batmemoria * bat_memoria){
    int * registros_temp, * memoria_temp;
    memoria_temp = bat_memoria->memoria;
    registros_temp = bat_memoria->registro_das_posicoes;
    bat_memoria->memoria = calloc(bat_memoria->espaco_total,sizeof(int));
    bat_memoria->registro_das_posicoes = calloc(bat_memoria->espaco_total,sizeof(int));
    for (int i = 0; i < (bat_memoria->espaco_total)/2; i++){
        bat_memoria->memoria[i] = memoria_temp[i];
        bat_memoria->registro_das_posicoes[i] = registros_temp[i];
    }
    free(memoria_temp);
    free(registros_temp);
}

//tam = 3  / cont = 0  / posicao = 5  /  2 0 0 1 0 0 0 0

int encontrar_posicao(int tamanho_do_espaco, batmemoria *bat_memoria){
    int posicao=0, encontrou_posicao=0, contador=0;
    while(!encontrou_posicao){
        if (!bat_memoria->registro_das_posicoes[posicao]){ //Se o valor dessa posicao original for 0
            for (contador=0; contador<tamanho_do_espaco; contador++){
                if ((posicao+contador) >= bat_memoria->espaco_total){
                    bat_memoria->espaco_total *= 2;
                    dobrar_memoria(bat_memoria);
                    }
                if (bat_memoria->registro_das_posicoes[posicao+contador]){ //Se o valor dessa posicao for diferente de 0
                    posicao+=(contador+bat_memoria->registro_das_posicoes[posicao+contador]+1);
                    break;
                }
                if (contador == tamanho_do_espaco-1)
                    return posicao;
            }
        } else {
            posicao+=bat_memoria->registro_das_posicoes[posicao]+1;
            if (posicao >= bat_memoria->espaco_total){
                bat_memoria->espaco_total *= 2;
                dobrar_memoria(bat_memoria);
            }
        }
    }
    return posicao;
}

void bat_alloc(batmemoria * bat_memoria){
    //bat-alloc 5 10 12 16 18 42
    int tamanho, posicao, temp;
    scanf(" %d", &tamanho);
    bat_memoria->espaço_usado+=tamanho+1;
    posicao = encontrar_posicao(tamanho+1, bat_memoria);
    printf("%d\n", posicao);
    bat_memoria->memoria[posicao] = tamanho;
    bat_memoria->registro_das_posicoes[posicao] = tamanho;
    for (int c = 1; c<=tamanho; c++){
        scanf(" %d", &temp);
        bat_memoria->memoria[posicao+c] = temp;
    }
}

void diminui_tamanho(batmemoria * bat_memoria){
    int *memoria_temp = bat_memoria->memoria;
    int *registro_temp = bat_memoria->registro_das_posicoes;
    bat_memoria->memoria = calloc(bat_memoria->espaco_total, sizeof(int));
    bat_memoria->registro_das_posicoes = calloc(bat_memoria->espaco_total, sizeof(int));
    for (int i = 0; i<bat_memoria->espaco_total; i++){
        bat_memoria->memoria[i] = memoria_temp[i];
        bat_memoria->registro_das_posicoes[i] = registro_temp[i];
    }
    free(registro_temp);
    free(memoria_temp);
}

void bat_free(batmemoria * bat_memoria){
    int endereco;
    scanf(" %d", &endereco);
    int tamanho_vetor = bat_memoria->memoria[endereco];
    bat_memoria->espaço_usado-= (tamanho_vetor+1);
    bat_memoria->memoria[endereco] = 0;
    bat_memoria->registro_das_posicoes[endereco] = 0;
    for (int i = 0; i<tamanho_vetor; i++){
        bat_memoria->memoria[endereco+1+i] = 0;
    }
    //testar se o tamanho do vetor deve ser reduzido
    int tamanho_total = bat_memoria->espaco_total;
    if (tamanho_total>8){
        //ver se tem alguma coisa depois do primeiro quarto do vetor
        for(int i = tamanho_total/4; i<tamanho_total; i++){
            if (bat_memoria->memoria[i]!=0)
                return;
        }
        bat_memoria->espaco_total /=2;
        diminui_tamanho(bat_memoria);
    }
}

void bat_print(batmemoria * bat_memoria){
    int endereco;
    scanf(" %d", &endereco);
    printf("%d", bat_memoria->memoria[endereco+1]);
    for (int i=2; i<=bat_memoria->memoria[endereco]; i++){
        printf(" %d", bat_memoria->memoria[endereco+i]);
    }
    printf("\n");
}

void bat_uso(batmemoria * bat_memoria){
    printf("%d de %d\n", bat_memoria->espaço_usado, bat_memoria->espaco_total);
}

void executar_comando(int comando, batmemoria *bat_memoria){
    if (comando == 1)
        bat_alloc(bat_memoria);
    else if (comando == 2)
        bat_free(bat_memoria);
    else if (comando == 3)
        bat_print(bat_memoria);
    else if (comando == 4)
        bat_uso(bat_memoria);
}

void liberar_batmemoria(batmemoria * bat_memoria){
    free(bat_memoria->memoria);
    free(bat_memoria->registro_das_posicoes);
    free(bat_memoria);
}