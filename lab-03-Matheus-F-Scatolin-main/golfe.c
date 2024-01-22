#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"
#include "partida.h"

//Função principal
int main(void) {
    int num_partidas;
    scanf("%d", &num_partidas);
    partida part;
    for (int c = 0; c < num_partidas; c++) {
        part = ler_partida(c + 1);
        imprimir_relatorio(part);
    }
    return 0;
}
