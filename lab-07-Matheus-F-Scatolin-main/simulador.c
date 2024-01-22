#include <stdio.h>
#include <stdlib.h>
#include "peca.h"
#include "esteira.h"
#include "pilha.h"
#include "funcionario.h"

int main(){
    printf("##### Simulação\n");
    p_peca peca;

    int tamanho_max_pilha, tamanho_max_esteira;
    scanf(" %d", &tamanho_max_esteira);
    p_esteira esteira = criar_esteira(tamanho_max_esteira);

    scanf(" %d", &tamanho_max_pilha);
    p_pilha pilha = criar_pilha(tamanho_max_pilha);

    p_funcionario classificador = criar_funcionario(1);
    p_funcionario embalador = criar_funcionario(2);
    int n_total_pecas = 0, n_pecas_embaladas = 0, n_pecas_lidas = 0;
    int peca_entrou_classificacao, peca_saiu_classificacao, peca_entrou_embalagem, peca_saiu_embalagem;
    scanf(" %d", &n_total_pecas);
    int minutos_atraso = 0, minuto_atual=0;
    while (n_pecas_embaladas<n_total_pecas){
        minuto_atual += 1;
        peca_entrou_classificacao = 0;
        peca_entrou_embalagem = 0;
        peca_saiu_classificacao = 0;
        peca_saiu_embalagem = 0;
        //Contabilizar 1 minuto de trabalho na peça para o embalador (se ele estiver com uma peça)
        if (!esta_livre(embalador))
            contar_minuto(embalador);
        //Testar se o embalador terminou o serviço
        if (mostrar_minutos_restantes(embalador) == 0){
            n_pecas_embaladas += 1;
            liberar_peca(passar_a_peca(embalador));
            peca_saiu_embalagem = 1;
        }
        //Testar se o embalador deve pegar uma nova peça p/ embalar
        if (esta_livre(embalador)&& pilha_tem_peca(pilha)){
            peca = desempilhar(pilha);
            pegar_peca(embalador, peca);
        }
        //Contabilizar 1 minuto de trabalho na peca para o classificador (se ele estiver com uma peça)
        if (!esta_livre(classificador))
            contar_minuto(classificador);
        //Testar se o classificador terminou o serviço e se a pilha tem espaço
        if (mostrar_minutos_restantes(classificador) == 0 && pilha_tem_espaco(pilha)){
            peca = passar_a_peca(classificador);
            empilhar(pilha, peca);
            peca_saiu_classificacao = 1;
            peca_entrou_embalagem = 1;
        }
        //Testar se o classificador esta livre e se tem peças na esteira
        if (esta_livre(classificador) && esteira_tem_peca(esteira)){
            peca = retirar_peca(esteira);
            pegar_peca(classificador, peca);
        }
        //Testar se a esteira tem espaço (se tiver, ler uma nova peca)
        if (tem_espaco(esteira)&&n_pecas_lidas!=n_total_pecas){
            peca = ler_e_criar_peca();
            adicionar_peca(esteira, peca);
            n_pecas_lidas += 1;
            peca_entrou_classificacao = 1;
        }
        //Se a esteira não tiver espaço e tiverem peças esperando, há um minuto de atraso
        else{
            if (n_pecas_lidas<n_total_pecas)
                minutos_atraso += 1;
        }
        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", minuto_atual, peca_entrou_classificacao, peca_saiu_classificacao, peca_entrou_embalagem, peca_saiu_embalagem);
    }
    printf("Tempo atraso: %d.", minutos_atraso);

    liberar_esteira(esteira);
    liberar_funcionario(classificador);
    liberar_funcionario(embalador);
    liberar_pilha(pilha);

    return 0;
}