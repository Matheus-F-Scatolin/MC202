#ifndef PARTIDA_H
#define PARTIDA_H

#include "circuito.h"

typedef struct _partida {
    float valor_aluguel;
    int identificacao, n_participantes, n_circuitos, n_equipamentos;
    circuito *circuitos;
} partida;

partida ler_partida(int identificacao);

void imprimir_relatorio(partida part);

int somar_jogadas(int indice_jogador, partida part);

int encontrar_circ_dificil(partida part);

#endif