#include <stdio.h>
#include <stdlib.h>
#include "lista_livros.h"

int main(){
    int comando=0, posicao=0;
    lista_livros *lista = criar_lista();
    comando = ler_comando();
    while (comando){ //Enquanto o comando não for 0 (EOF)
        lista = executar_comando(lista, comando, &posicao);
        comando = ler_comando();
    }
    liberar_lista(lista);

    return 0;
}