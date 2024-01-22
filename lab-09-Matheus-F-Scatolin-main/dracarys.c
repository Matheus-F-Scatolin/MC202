#include <stdio.h>
#include <string.h>
#include "arvore.h"
#define MAX 202
#define TAMANHO_OPERADOR 2
#define N_LETRAS 53
enum tipo_de_linha {OPERACAO, DECLARACAO, NENHUM_DOS_ANTERIORES};
const char letras[N_LETRAS] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**
 * @brief Esta função recebe um caractere como entrada e verifica se ele é uma letra,
 * retornando 1 se for uma letra e 0 caso contrário.
 *
 * @param caractere O caractere a ser verificado.
 * @return 1 se o caractere for uma letra, 0 caso contrário.
 */
int eh_letra(char caractere){
    for (int c = 0; c<N_LETRAS-1; c++)
        if (letras[c] == caractere)
            return 1;
    return 0;
}

/**
 * @brief Esta função recebe uma palavra como entrada e verifica se ela corresponde a um dos
 * tipos de dados suportados (int, char, double, float).
 *
 * @param palavra A palavra a ser verificada.
 * @return 1 se a palavra for um tipo de dado, 0 caso contrário.
 */
int eh_tipo(char * palavra){
    if (strcmp(palavra, "int") == 0 ||
        strcmp(palavra, "char") == 0 ||
        strcmp(palavra, "double") == 0 ||
        strcmp(palavra, "float") == 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Esta função recebe uma linha como entrada e determina se a linha é uma operação, uma declaração
 * ou nenhum dos anteriores, retornando o tipo de linha correspondente.
 *
 * @param linha_atual A linha a ser verificada.
 * @return O tipo de linha (OPERACAO, DECLARACAO ou NENHUM_DOS_ANTERIORES).
 */
enum tipo_de_linha verificar_tipo_de_linha(char * linha_atual){
    //Se a linha tiver parênteses, ela não é nem declaração nem operação
    for (int c = 0; linha_atual[c]!='\0'; c++)
        if (linha_atual[c] == '(')
            return NENHUM_DOS_ANTERIORES;

    //Testar se é declaração (ver se a primeira palavra é um tipo)
    char primeira_palavra[MAX];
    sscanf(linha_atual, "%s", primeira_palavra);
    if (eh_tipo(primeira_palavra))
        return DECLARACAO;

    //Se a primeira palavra da linha for um "return", então a linha não é nem operação nem declaração
    if (strcmp(primeira_palavra, "return") == 0)
        return NENHUM_DOS_ANTERIORES;

    //Se não for nenhum dos casos acima, então só pode ser uma é operação
    return OPERACAO;
}

/**
 * @brief Esta função recebe uma linha como entrada e formata a linha, removendo espaços em branco iniciais e
 * o ponto e vírgula ou '\n' final, se presente.
 *
 * @param buffer O buffer que armazena a linha a ser formatada.
 */
void formata_linha(char buffer[]){
    char linha_original[MAX];
    strcpy(linha_original, buffer);

    //encontrar o primeiro caractere que não seja um espaço
    int inicio = 0;
    for (inicio = 0; linha_original[inicio] == ' '; inicio ++);

    //copiar para a linha formatada a linha original sem os espaços iniciais, e removendo o ; final (se houver).
    int pos_atual = 0;
    for (;(linha_original[inicio+pos_atual]!= '\n') && (linha_original[inicio+pos_atual]!= ';'); buffer[pos_atual] = linha_original[inicio+pos_atual], pos_atual++);
    buffer[pos_atual] = '\0';
}

int main(void){
    p_no raiz = criar_arvore();
    enum tipo_de_linha tipo_da_linha_atual;
    int numero_da_linha = 0, numero_de_erros = 0;
    char buffer[MAX];

    //Enquanto não for atingido o fim do arquivo
    while (fgets(buffer, MAX, stdin) != NULL){
        formata_linha(buffer);
        numero_da_linha += 1;
        //Toda linha cuja primeira palavra não começa com uma letra, pode ser ignorada.
        if (eh_letra(buffer[0])){

            //Classificar cada linha útil como sendo uma operação ou declaração
            tipo_da_linha_atual = verificar_tipo_de_linha(buffer);

            //Se for uma operação:
            if (tipo_da_linha_atual == OPERACAO){
                //Supondo que a linha é do tipo "var1 = var2 + var3;"
                //Definir cada uma das variáveis
                char var1[MAX], var2[MAX], var3[MAX], operador[TAMANHO_OPERADOR];
                sscanf(buffer, "%s %s %s %s %s", var1, operador, var2, operador, var3);
                //Definir o tipo de cada uma das variáveis
                enum tipo_da_variavel tipo_var1, tipo_var2, tipo_var3;
                tipo_var1 = verificar_definicao_e_tipo(var1, raiz);
                tipo_var2 = verificar_definicao_e_tipo(var2, raiz);
                tipo_var3 = verificar_definicao_e_tipo(var3, raiz);

                //Agora, basta verificar:
                //1. Se os três símbolos usados estão definidos.
                if (tipo_var1 == NAO_ESTA_DEFINIDO){
                    printf("Linha %d: o símbolo %s não foi definido.\n", numero_da_linha, var1);
                    numero_de_erros += 1;
                }
                else if (tipo_var2 == NAO_ESTA_DEFINIDO){
                    printf("Linha %d: o símbolo %s não foi definido.\n", numero_da_linha, var2);
                    numero_de_erros += 1;
                }
                else if (tipo_var3 == NAO_ESTA_DEFINIDO){
                    printf("Linha %d: o símbolo %s não foi definido.\n", numero_da_linha, var3);
                    numero_de_erros += 1;
                }
                //2. Se os tipos do segundo símbolo e terceiro são diferentes para serem operados.
                else if (tipo_var2 != tipo_var3){
                    printf("Linha %d: tipos incompatíveis: %s (%s) %s %s (%s).\n",numero_da_linha, var2, tipo_da_variavel_em_texto(tipo_var2), operador, var3, tipo_da_variavel_em_texto(tipo_var3));
                    numero_de_erros += 1;
                }
                //3. Se o resultado da operação possui o mesmo tipo que a variável que o receberá.
                else if (tipo_var1 != tipo_var2){
                    printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", numero_da_linha, var1, tipo_da_variavel_em_texto(tipo_var1), tipo_da_variavel_em_texto(tipo_var2));
                    numero_de_erros += 1;
                }
            }

            //Se for uma declaração, adicionar a variável à tabela de símbolos:
            else if (tipo_da_linha_atual == DECLARACAO){
                char simbolo[MAX], tipo[MAX];
                sscanf(buffer, "%s %s", tipo, simbolo);
                raiz = inserir_elemento(raiz, simbolo, texto_em_tipo_da_variavel(tipo));
            }
        }
    }

    if (numero_de_erros == 0)
        printf("Não há erros de tipo.\n");
    //Imprimir os símbolos (e seus tipos) em ordem alfabética
    imprimir_arvore_inordem(raiz);

    //Liberar a árvore toda
    liberar_arvore(raiz);

    return 0;
}