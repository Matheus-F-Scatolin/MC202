#include <stdio.h>
#include <stdlib.h>

/* 
Esta função aloca dinamicamente uma matriz de inteiros usando a função malloc.
Parâmetros:
    - int *** matriz: O endereço de memória no qual a matriz será alocada.
    - int n_linhas: O número de linhas da matriz que será alocada.
Retorna:
    - void
*/
void alocar_matriz(int *** matriz, int n_linhas){
    (*matriz) = malloc(n_linhas * sizeof(int *));
    for (int c = 0; c<n_linhas; c++)
        (*matriz)[c] = malloc(n_linhas*sizeof(int));
}

/* 
Esta função libera a memória previamente alocada para uma matriz de inteiros.
Parâmetros:
    - int ** matriz: A matriz a ser liberada.
    - int n_linhas: O número de linhas da matriz.
Retorna:
    - void.
*/
void liberar_matriz(int ** matriz, int n_linhas){
    for (int c=0; c<n_linhas; c++)
        free(matriz[c]);
    free(matriz);
}

/* 
Esta função lê valores inteiros em uma matriz a partir da entrada padrão.
Parâmetros:
    - int ** matriz: A matriz na qual os valores serão lidos.
    - int n_linhas: O número de linhas da matriz.
Retorna:
    - void.
*/
void ler_matriz(int **matriz, int n_linhas){
    for (int i = 0; i<n_linhas; i++)
        for (int j = 0; j<n_linhas; j++){
            scanf(" %d", &matriz[i][j]);
        }
}

/* 
Esta função imprime uma matriz de inteiros na saída padrão.
Parâmetros:
    - int ** matriz: A matriz a ser impressa.
    - int n_linhas: O número de linhas da matriz.
Retorna:
    - void.
*/
void imprimir_matriz(int **matriz, int n_linhas){
    for (int i = 0; i < n_linhas; i++){
        printf("%d", matriz[i][0]);
        for (int j = 1; j < n_linhas; j++){
            printf("\t%d", matriz[i][j]);
        }
        printf("\n");
    }
}

/* 
Esta função permite alterar um elemento específico em uma matriz.
Sua lógica inclui a leitura das coordenadas da alteração e do novo valor.
Parâmetros:
    - int ** matriz: A matriz na qual o elemento será alterado.
Retorna:
    - void.
*/
void alterar_elemento(int **matriz){
    int linha, coluna, novo_valor;
    scanf(" %d %d %d", &linha, &coluna, &novo_valor);
    matriz[linha][coluna] = novo_valor;
}

/* 
Esta função calcula a soma das linhas e colunas de uma matriz, excluindo as 4 pontas.
Parâmetros:
    - int ** matriz: A matriz na qual as somas serão calculadas.
    - int n_linhas: O número de linhas da matriz.
    - int * ultima_linha: Uma variável para armazenar a soma da última linha.
    - int * primeira_linha: Uma variável para armazenar a soma da primeira linha.
    - int * ultima_coluna: Uma variável para armazenar a soma da última coluna.
    - int * primeira_coluna: Uma variável para armazenar a soma da primeira coluna.
Retorna:
    - void
*/
void soma_linhas_e_colunas(int ** matriz, int n_linhas, int * ultima_linha, int * primeira_linha, int * ultima_coluna, int * primeira_coluna){
    for (int c=1; c<n_linhas-1; c++){
        *ultima_linha += (matriz)[n_linhas-1][c];
        *ultima_coluna += (matriz)[c][n_linhas-1];
        *primeira_coluna += (matriz)[c][0];
        *primeira_linha += (matriz)[0][c];
    }
}

/* 
Esta função encontra o setor com a maior soma em um conjunto de setores.
Parâmetros:
    - int * setores: Um vetor de inteiros contendo as somas de diferentes setores.
Retorna:
    - int maior_setor: O número do setor com a maior soma (0, 1, 2 ou 3).
*/
int encontra_maior_setor(int * setores){
    int maior_setor = 0, maior_soma = setores[0];
    for (int c=0; c<3; c++){
        if (setores[c+1] > maior_soma){
            maior_setor = c+1;
            maior_soma = setores[c+1];
            }
    }
    return maior_setor;
}

/* 
Esta função reduz o tamanho de uma matriz, removendo uma linha e uma coluna específicas.
Parâmetros:
    - int *** matriz: O endereço de memória da matriz a ser reduzida.
    - int n_linhas: O número de linhas da matriz original.
    - int maior_setor: O número do setor a ser removido (0, 1, 2 ou 3).
Retorna:
    - void.
*/
void reduzir_tamanho_matriz(int *** matriz, int n_linhas, int maior_setor){
    /*Definir o quanto cada linha e coluna da matriz original deve mudar
    para que ela se encaixe na nova matriz*/
    int variacao_linha = 0, variacao_coluna = 0;
    //Se maior_setor=1, não precisa mudar nada
    if (maior_setor == 1)
        variacao_coluna = 1;
    else if (maior_setor == 2)
        variacao_linha = 1;
    else if (maior_setor == 3){
        variacao_coluna = 1;
        variacao_linha = 1;
    }

    int ** nova_matriz;
    alocar_matriz(&nova_matriz, n_linhas-1);
    for (int i=0; i<n_linhas-1; i++)
        for (int j=0; j<n_linhas-1; j++)
            if ((i + variacao_linha) >= 0 && (i + variacao_linha) <= n_linhas-1 &&
                (j + variacao_coluna) >= 0 && (j + variacao_coluna) <= n_linhas-1)
                nova_matriz[i][j] = (*matriz)[i + variacao_linha][j + variacao_coluna];
    liberar_matriz(*matriz, n_linhas);
    *matriz = nova_matriz;
}

/* 
Esta função permite escolher um setor específico em uma matriz, sendo eles:
Setor 0: superior esquerdo
Setor 1: superior direito
Setor 2: inferior esquerdo
Setor 3: inferior direito
Parâmetros:
    - int *** matriz: O endereço de memória da matriz na qual o setor será escolhido.
    - int n_linhas: O número de linhas da matriz original.
Retorna:
    - void.
*/
void escolher_setor(int ***matriz, int n_linhas){
    int ultima_linha=0, primeira_linha=0, primeira_coluna=0, ultima_coluna=0;
    soma_linhas_e_colunas(*matriz, n_linhas, &ultima_linha, &primeira_linha, &ultima_coluna, &primeira_coluna);
    
    int * setores, maior_setor;
    setores = malloc(4*sizeof(int));
    setores[0] = primeira_linha + primeira_coluna+(*matriz)[0][0];
    setores[1] = primeira_linha + ultima_coluna+(*matriz)[0][n_linhas-1];
    setores[2] = ultima_linha + primeira_coluna+(*matriz)[n_linhas-1][0];
    setores[3] = ultima_linha + ultima_coluna+(*matriz)[n_linhas-1][n_linhas-1];

    maior_setor = encontra_maior_setor(setores);
    free(setores);

    reduzir_tamanho_matriz(matriz, n_linhas, maior_setor);
}

//Função principal
int main(void){
    int n_linhas, **matriz=NULL;
    scanf("%d", &n_linhas);
    alocar_matriz(&matriz, n_linhas);
    ler_matriz(matriz, n_linhas);
    printf("Quadras:\n");
    imprimir_matriz(matriz, n_linhas);
    escolher_setor(&matriz, n_linhas);

    //Antes de perguntar qualquer coisa, reduzir a matriz
    n_linhas-=1;
    printf("\n");
    printf("Conjuntos que precisam de atenção:\n");
    imprimir_matriz(matriz, n_linhas);
    
    int operacao = 1;
    while (operacao&&n_linhas>=2){
        scanf(" %d", &operacao);
        if (!operacao)
            break;
        alterar_elemento(matriz);
        escolher_setor(&matriz, n_linhas);
        n_linhas -= 1;
        printf("\n");
        printf("Conjuntos que precisam de atenção:\n");
        imprimir_matriz(matriz, n_linhas);
    }


    if (n_linhas == 2 && operacao){
        escolher_setor(&matriz, n_linhas);
        printf("\n");
        printf("Conjuntos que precisam de atenção:\n");
        n_linhas = 1;
        imprimir_matriz(matriz, n_linhas);
    }
    liberar_matriz(matriz, n_linhas);
    return 0;
}