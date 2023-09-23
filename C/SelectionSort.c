#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double Executa_caso(char *nomeArquivo, int tamanho);
int *RecebeCSV(char *nomeArquivo, int tamanho);
void SelectionSort(int *vetor, int tamanho);

int main()
{
    double tempo, media;
    int i;

    printf("---------Caso de Teste---------\n");
    media = 0;

    for (i = 1; i <= 1; i++)
    {
        tempo = Executa_caso("1000000qo.csv", 1000000); //(nome_do_arquivo_csv, num_de_linhas)
        media += tempo;
        printf("Tempo %i: %f\n", i, tempo);
    }
    media /= 3;
    printf("Média: %f\n", media);

    return 0;
}

/*
Executa_caso("1000.csv",1000)
Executa_caso("1000i.csv",1000)
Executa_caso("1000qo.csv",999)

Executa_caso("10000.csv",10000)
Executa_caso("10000i.csv",10000)
Executa_caso("10000qo.csv",9999)

Executa_caso("100000.csv",100000)
Executa_caso("100000i.csv",100000)
Executa_caso("100000qo.csv",99999)
*/

/*Executa o teste de ordenação e retorna o tempo de duração do algoritmo
--- Recebe ---
(char*) nomeArquivo: nome do arquivo .CSV
(int) tamanho: qtd de linhas no arquivo .CSV
--- Retorno ---
(double) duracao: tempo de execução em segundos
*/
double Executa_caso(char *nomeArquivo, int tamanho)
{
    int i, *vetor;
    double duracao;
    clock_t start, end;

    tamanho = tamanho - 1; // Ajuste para tamanho real

    // vetor com valores do CSV
    vetor = RecebeCSV(nomeArquivo, tamanho);

    // faz ordenação
    start = clock();
    SelectionSort(vetor, tamanho);
    end = clock();

    // calcula tempo do algoritimo
    duracao = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    free(vetor);

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
    int *vetor, i = 0;
    char cabecalho[4];
    vetor = malloc(sizeof(int) * tamanho);
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "r");

    // Le e ignora o cabeçalho
    fscanf(arquivo, "%*s\n");

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

/*Faz a ordenação pelo método selectin sort
--- Recebe ---
(int*) vetor: ponteiro para vetor de inteiros a serem ordenados
(int) tamanho: tamanho do vetor
*/
void SelectionSort(int *vetor, int tamanho)
{
    int i, j, min, aux;
    for (i = 0; i < tamanho - 1; i++)
    {
        min = i;
        for (j = i + 1; j < tamanho; j++)
        {
            if (vetor[min] > vetor[j])
            {
                min = j;
            }
        }
        aux = vetor[min];
        vetor[min] = vetor[i];
        vetor[i] = aux;
    }

    return;
}
