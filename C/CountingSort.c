#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double Executa_caso(char *nomeArquivo, int tamanho);
int *RecebeCSV(char *nomeArquivo, int tamanho);
void CountingSort(int *vetorA, int *vetorB, int tamanho, int max);

int main()
{
    double tempo, media;
    int i;

    printf("---------Caso de Teste---------\n");
    media = 0;
    for (i = 1; i <= 3; i++)
    {
        tempo = Executa_caso("1000qo.csv", 1000); //(nome_do_arquivo_csv, num_de_linhas)
        media += tempo;
        printf("Tempo %i: %f\n", i, tempo);
    }
    media /= 3;
    printf("Média: %f\n", media);

    return 0;
}

/*Executa o teste de ordenação e retorna o tempo de duração do algoritmo
--- Recebe ---
(char*) nomeArquivo: nome do arquivo .CSV
(int) tamanho: qtd de linhas no arquivo .CSV
--- Retorno ---
(double) duracao: tempo de execução em segundos
*/
double Executa_caso(char *nomeArquivo, int tamanho)
{
    int i, *vetor, max, *vetorB;
    double duracao;
    clock_t start, end;

    vetorB = (int *)calloc(tamanho, sizeof(int));

    // vetor com valores do CSV
    vetor = RecebeCSV(nomeArquivo, tamanho);

    vetorB[0] = -1;
    for (i = 1, max = vetor[i]; i < tamanho; i++)
    {
        if (max < vetor[i])
        {
            max = vetor[i];
        }
        vetorB[i] = -1; // Preenchendo vetorB com flag
    }

    start = clock();
    CountingSort(vetor, vetorB, tamanho, max);
    end = clock();

    duracao = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    free(vetor);
    free(vetorB);

    return duracao;
}

/*Lê arquivo CSV e insere em um vetor
--- Recebe ---
(char*) nomeArquivo: nome do arquivo .CSV
(int) tamanho: qtd de linhas no arquivo .CSV

--- Retorna ---
(int*) vetor: ponteiro para vetor com valores preenchidos
*/
int *RecebeCSV(char *nomeArquivo, int tamanho)
{
    int *vetor, i = 1;
    char cabecalho[4];
    vetor = malloc(sizeof(int) * tamanho);
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "r");

    // Le e ignora o cabeçalho
    fscanf(arquivo, "%*s\n");

    vetor[0] = -1;
    // Lê linha a linha do arquivo até que encontre o fim do arquivo
    do
    {
        // Ignora primeira coluna(index) e guarda valor da segunda coluna
        fscanf(arquivo, "%*i,%i\n", &vetor[i]);
        i++;
    } while (!feof(arquivo));
    fclose(arquivo);

    return vetor;
}

/*Faz a ordenação pelo método counting sort
--- Recebe ---
(int*) vetorA: ponteiro para vetor de inteiros a serem ordenados
(int*) vetorB: ponteiro para vetor de inteiros ordenado
(int) tamanho: tamanho do vetorA
(int) max: maior valor dentro do vetorA
*/
void CountingSort(int *vetorA, int *vetorB, int tamanho, int max)
{
    int *vetorC, j, i;
    vetorC = calloc(max + 1, sizeof(int));

    for (j = 1; j < tamanho; j++)
    {
        vetorC[vetorA[j]] = vetorC[vetorA[j]] + 1;
    }

    for (i = 1; i <= max; i++)
    {
        vetorC[i] = vetorC[i] + vetorC[i - 1];
    }

    for (j = tamanho - 1; j > 0; j--)
    {
        vetorB[vetorC[vetorA[j]]] = vetorA[j];
        vetorC[vetorA[j]] = vetorC[vetorA[j]] - 1;
    }

    free(vetorC);
    return;
}
