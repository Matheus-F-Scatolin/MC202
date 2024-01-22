#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "familia.h"
/*o vetor, por padrão possui 1999 posições (1999 é primo e como
o máximo de famílias é igual a 1500, sempre haverá espaço livre)*/
#define TAMANHO_VETOR 1999
#define PROP_AUREA 1.618033988749895

typedef struct hash_table * p_hash_table;

struct hash_table{
    p_familia * vetor;
};

/**
 * @brief Cria uma nova tabela hash e a retorna.
 *
 * @return Um ponteiro para a nova tabela hash.
 */
p_hash_table criar_hash_table();

/**
 * @brief Libera a memória alocada para a tabela hash, incluindo as famílias armazenadas.
 *
 * @param hash_table A tabela hash a ser liberada.
 */
void liberar_hash_table(p_hash_table hash_table);

/**
 * @brief Insere uma nova família na tabela hash.
 *
 * @param nome_da_familia O nome da família a ser inserida.
 * @param n_doces A quantidade inicial de doces da família.
 * @param hash_table A tabela hash onde a família será inserida.
 */
void inserir_na_hash_table(char * nome_da_familia, int n_doces, p_hash_table hash_table);

/**
 * @brief Encontra a posição de uma família na tabela hash pelo seu nome.
 *
 * @param nome_da_familia O nome da família a ser procurada.
 * @param hash_table A tabela hash onde a família será procurada.
 * 
 * @return A posição da família na tabela hash.
 */
int encontrar_posicao_da_familia(char * nome_da_familia, p_hash_table hash_table);

/**
 * @brief Remove uma família da tabela hash, marcando sua posição como vazia.
 * (setando n_doces = -1)
 *
 * @param nome_da_familia_atual O nome da família a ser removida.
 * @param hash_table A tabela hash onde a família será removida.
 */
void remover_da_hash_table(char * nome_da_familia_atual, p_hash_table hash_table);

/**
 * @brief Encontra o número de doces de uma família na tabela hash pelo seu nome.
 *
 * @param nome_da_familia O nome da família.
 * @param hash_table A tabela hash onde a família será procurada.
 * 
 * @return O número de doces da família.
 */
int encontrar_numero_de_doces(char * nome_da_familia, p_hash_table hash_table);

/**
 * @brief Atualiza o número de doces de uma família na tabela hash pelo seu nome.
 *
 * @param nome_da_familia_atual O nome da família a ser atualizada.
 * @param variacao_doces A quantidade de doces a ser adicionada ou removida.
 * @param hash_table A tabela hash onde a família será atualizada.
 */
void atualizar_na_hash_table(char * nome_da_familia_atual, int variacao_doces, p_hash_table hash_table);
#endif