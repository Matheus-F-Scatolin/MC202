#ifndef BATMEMORIA_H
#define BATMEMORIA_H

typedef struct _batmemoria
{
    int espaco_total;            // Espaço total disponível na memória.
    int espaço_usado;            // Espaço atualmente em uso na memória.
    int *registro_das_posicoes;  // Vetor que guarda o tamanho dos subvetores.
    int *memoria;                // Memória principal onde os dados são armazenados.
} batmemoria;

/*
Cria e inicializa uma estrutura batmemoria.

Retorno:
- Retorna um ponteiro para a estrutura criada (batmemoria *).
*/
batmemoria * criar_batmemoria();

/*
Dobra o tamanho da memória principal e do vetor de registros, copiando os valores antigos.

Parâmetros:
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void dobrar_memoria(batmemoria *bat_memoria);

/*
Lê um comando e retorna um inteiro que representa o comando:

Comandos:
1 - bat-alloc
2 - bat-free
3 - bat-print
4 - bat-uso

Retorno:
- Retorna o número do comando lido.
- Retorna -1 em caso de erro.
*/
int ler_comando(void);

/*
Executa um comando na batmemória com base no número do comando e na estrutura da batmemória.

Parâmetros:
- comando: O número do comando a ser executado.
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void executar_comando(int comando, batmemoria *bat_memoria);

/*
Aloca espaço na memória principal para armazenar dados.

Parâmetros:
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void bat_alloc(batmemoria *bat_memoria);

/*
Libera espaço na memória principal de acordo com um endereço.

Parâmetros:
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void bat_free(batmemoria *bat_memoria);

/*
Imprime os dados armazenados em uma posição da memória principal.

Parâmetros:
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void bat_print(batmemoria *bat_memoria);

/*
Imprime a quantidade de espaço em uso e o espaço total da memória principal.

Parâmetros:
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void bat_uso(batmemoria *bat_memoria);

/*
Libera a memória alocada para a estrutura batmemoria.

Parâmetros:
- bat_memoria: Ponteiro para a estrutura batmemoria.
*/
void liberar_batmemoria(batmemoria *bat_memoria);

#endif