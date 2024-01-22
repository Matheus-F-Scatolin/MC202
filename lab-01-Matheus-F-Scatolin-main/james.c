#include <stdio.h>
#define MAX 100000

int calcular_posicao(int preco_da_salada) {
    //achar a posição em que a salada atual deve ser adicionada
    int posicao = (preco_da_salada-4)/3;
    return posicao;
}

void imprimir_resultado(int vendas_por_tipo[],int maior_sequencia,int salada_sequencia) {
    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", vendas_por_tipo[0], vendas_por_tipo[1], vendas_por_tipo[2]);
    printf("James vendeu %d saladas de %d reais consecutivamente", maior_sequencia, salada_sequencia);
}

void ler_vetor_vendas(int vetor_vendas[], int n_vendas){
    for (int i=0; i<n_vendas; i++){
        scanf("%d", &vetor_vendas[i]);
    }
}

void contar_numero_vendas(int vetor_vendas[], int vendas_por_tipo[], int n_vendas){
    int posicao;
    for (int i = 0; i< n_vendas; i++){
        posicao = calcular_posicao(vetor_vendas[i]);
        vendas_por_tipo[posicao] ++;
    }
}

void encontrar_sequencia(int n_vendas, int vetor_vendas[], int vetor_sequencia[]) {
    int contador = 0, salada_da_vez = vetor_vendas[0];
    for (int i = 0; i< n_vendas; i++){
        if (salada_da_vez == vetor_vendas[i]) {
            contador++;
        } else{
            contador = 1;
            salada_da_vez = vetor_vendas[i];
        }
        if (contador > vetor_sequencia[1]){
            vetor_sequencia[1] = contador;
            vetor_sequencia[0] = vetor_vendas[i];
        }
    }
}

int main(void){
    int n_vendas, vetor_vendas[MAX]; 
    scanf("%d", &n_vendas);

    ler_vetor_vendas(vetor_vendas, n_vendas);
    int vendas_por_tipo[3] = {0, 0, 0}; // posição 0 p/ 5 reais, pos 2 p/ 7 reais e pos 3 p/ 10 reais
    contar_numero_vendas(vetor_vendas, vendas_por_tipo, n_vendas);

    int vetor_sequencia[2] = {vetor_vendas[0], 0}; // {salada_da_sequencia, tamanho_da_sequencia}
    encontrar_sequencia(n_vendas, vetor_vendas, vetor_sequencia);

    imprimir_resultado(vendas_por_tipo, vetor_sequencia[1], vetor_sequencia[0]);
    return 0;
}