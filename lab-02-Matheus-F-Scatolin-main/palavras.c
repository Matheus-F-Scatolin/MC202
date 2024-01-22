#include <stdio.h>
#define MAX 300
#define MAX_PALAVRA 20

// Função para ler uma matriz de letras
void ler_matriz(char matriz_letras[][MAX], int n_linhas, int n_colunas)
{
	for (int i = 0; i < n_linhas; i++)
		for (int j = 0; j < n_colunas; j++)
			scanf(" %c", &matriz_letras[i][j]);
}

// Função para calcular o tamanho de uma string
int tamanho_palavra(char palavra[])
{
	int i;
	for (i = 0; palavra[i] != '\0'; i++);
	return i;
}

/*Função para buscar uma palavra na matriz de letras, procurando
horizontalmente e verticalmente, em ambos os sentidos*/
int buscar_palavra(char palavra[], char matriz_letras[][MAX], int n_linhas, int n_colunas)
{
	for (int i = 0; i < n_linhas; i++){
		for (int j = 0; j < n_colunas; j++)
		{
			int letra_correta = 1;
			if (matriz_letras[i][j] == palavra[0])
			{
			 	//Buscar para cima
				if (tamanho_palavra(palavra) <= i + 1)
				{
					for (int c = 1; c < tamanho_palavra(palavra); c++)
					{
						if (palavra[c] != matriz_letras[i - c][j])
						{
							letra_correta = 0;
							break;
						}
					}

					if (letra_correta) return 1;	//Encontrou a palavra
				}

				//Buscar para baixo
				letra_correta = 1;
				if (tamanho_palavra(palavra) <= n_linhas - i)
				{
					for (int c = 1; c < tamanho_palavra(palavra); c++)
					{
						if (palavra[c] != matriz_letras[i + c][j])
						{
							letra_correta = 0;
							break;
						}
					}

					if (letra_correta) return 1;
				}

				//Buscar para a esquerda
				letra_correta = 1;
				if (tamanho_palavra(palavra) <= j + 1)
				{
					for (int c = 1; c < tamanho_palavra(palavra); c++)
					{
						if (palavra[c] != matriz_letras[i][j - c])
						{
							letra_correta = 0;
							break;
						}
					}

					if (letra_correta)
                        return 1;
				}

				//Buscar para a direita
				letra_correta = 1;
				if (tamanho_palavra(palavra) <= n_colunas - j)
				{
					for (int c = 1; c < tamanho_palavra(palavra); c++)
					{
						if (palavra[c] != matriz_letras[i][j + c])
						{
							letra_correta = 0;
							break;
						}
					}

					if (letra_correta) return 1;
				}
			}
		}
    }
	return 0;	//Não encontrou a palavra
}

// Função para verificar várias palavras na matriz de letras
void verificar_palavras(int n_palavras, char palavras[][MAX_PALAVRA], char matriz_letras[][MAX], int n_linhas, int n_colunas)
{
	//Iterar pelas palavras do vetor "palavras"
	for (int c = 0; c < n_palavras; c++)
	{
		if (buscar_palavra(palavras[c], matriz_letras, n_linhas, n_colunas))
		{
			printf("A palavra %s está no texto!\n", palavras[c]);
		}
		else
		{
			printf("A palavra %s não está no texto!\n", palavras[c]);
		}
	}
}

int main(void)
{
	int n_linhas, n_colunas, n_palavras;
	scanf("%d %d %d", &n_linhas, &n_colunas, &n_palavras);

	char matriz_letras[MAX][MAX];
	ler_matriz(matriz_letras, n_linhas, n_colunas);

	char palavras[MAX][MAX_PALAVRA];
	for (int c = 0; c < n_palavras; c++) scanf("%s", palavras[c]);

	verificar_palavras(n_palavras, palavras, matriz_letras, n_linhas, n_colunas);
	return 0;
}
