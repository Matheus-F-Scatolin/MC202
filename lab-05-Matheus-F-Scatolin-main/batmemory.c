#include <stdio.h>
#include "batmemoria.h"

int main(){
    int n_comandos, comando;
    batmemoria *bat_memoria=NULL;
    bat_memoria = criar_batmemoria();
    scanf("%d", &n_comandos);
    for (int c = 0; c< n_comandos; c++){
        comando = ler_comando();
        executar_comando(comando, bat_memoria);
    }
    liberar_batmemoria(bat_memoria);
    return 0;
}
