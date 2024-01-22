#include "partida.h"
#include <stdio.h>
#include <stdlib.h>

/*
Dado um jogador e uma partida, essa função retorna
a soma das jogadas desse jogador na partida.
*/
int somar_jogadas(int indice_jogador, partida part){
    int soma=0;
    for (int c=0; c<part.n_circuitos; c++){
        soma+=part.circuitos[c].jogadas[indice_jogador];
    }
    return soma;
}

/*
Dada uma partida, essa função encontra o circuito
no qual, somados, os jogadores gastaram mais jogadas.
*/
int encontrar_circ_dificil(partida part){
    int maior_soma=0, soma_atual, circ_mais_dificil;
    for (int c=0; c<part.n_circuitos; c++){
        soma_atual = 0;
        for (int i=0; i<part.n_participantes; i++){
            soma_atual+=part.circuitos[c].jogadas[i];
        }
        if (soma_atual > maior_soma){
            maior_soma = soma_atual;
            circ_mais_dificil = part.circuitos[c].identificacao;
        }
    }
    return circ_mais_dificil;
}


/*
Dada uma partida, a função imprime seu relatorio,
chamando as funções somar_jogadas e encontrar_circ_dificil.
Ao final, ela libera os vetores dinamicamente alocados.
*/
void imprimir_relatorio(partida part){
    printf("Partida %d\n", part.identificacao);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n", part.n_participantes, part.n_circuitos, part.n_equipamentos);
    printf("Valor do Aluguel: R$ %.2f\n", part.valor_aluguel);
    for (int c=0; c<part.n_participantes; c++){
        printf("Jogador %d: %d\n", c+1, somar_jogadas(c, part));
    }
    printf("Circuito mais dificil: %d\n", encontrar_circ_dificil(part));

    printf("##########\n");
    for (int c = 0; c < part.n_circuitos; c++) {
        free(part.circuitos[c].jogadas);
    }
    free(part.circuitos);
}

/*
Dado um número de idenificação, essa função cria uma
uma partida, lendo seus atributos, e retorna ela.
*/
partida ler_partida(int identificacao){
    partida part;
    part.identificacao = identificacao;
    scanf(" %d %d %d", &part.n_participantes, &part.n_circuitos, &part.n_equipamentos);
    float aluguel;
    aluguel = 10*part.n_circuitos + 17.50*part.n_equipamentos;
    part.valor_aluguel = aluguel;

    part.circuitos = malloc(part.n_circuitos*sizeof(circuito));
    for (int c=0; c<part.n_circuitos; c++){
        part.circuitos[c] = ler_circuito(part.n_participantes);
    }

    if (part.circuitos == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    return part;
}