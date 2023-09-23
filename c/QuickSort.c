#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double Executa_caso(char *nomeArquivo, int tamanho);
int *RecebeCSV(char *nomeArquivo, int tamanho);
void QuickSort(int *vetor, int inicio, int final);
int Particiona(int *vetor, int inicio, int final);
void Swap(int *vetor, int index1, int index2);

int main()
{
    int i;
    double tempo, media;
    printf("---------Caso de Teste---------\n");
    media = 0;
    for (i = 1; i <= 3; i++)
    {
        tempo = Executa_caso("1000000.csv", 1000000); //(nome_do_arquivo_csv, num_de_linhas)
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
    int i, *vetor;
    double duracao;
    clock_t start, end;

    // ajustando para tamanho real do CSV
    tamanho = tamanho - 1;
    // vetor com valores do CSV
    vetor = RecebeCSV(nomeArquivo, tamanho);

    // faz ordenação
    start = clock();
    QuickSort(vetor, 0, tamanho - 1);
    end = clock();

    // calcula tempo do algoritimo
    duracao = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    // Libera vetor
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
    FILE *arquivo;

    vetor = malloc(sizeof(int) * tamanho); // aloca vetor

    arquivo = fopen(nomeArquivo, "r"); // abre arquivo

    // Le e ignora o cabeçalho
    fscanf(arquivo, "%*s\n");

    // Lê linha a linha do arquivo até que encontre o fim do arquivo
    do
    {
        // Ignora primeira coluna(index) e guarda valor da segunda coluna
        fscanf(arquivo, "%*i,%i\n", &vetor[i]);
        i++;
    } while (!feof(arquivo));

    fclose(arquivo); // fecha arquivo

    return vetor; // retorna vetor preenchido
}

/*Faz a ordenação pelo método quick-sort
--- Recebe ---
(int*) vetor: ponteiro para vetor de inteiros
(int) inicio: index do inicio do vetor
(int) final: index do final do vetor
*/
void QuickSort(int *vetor, int inicio, int final)
{
    if (inicio < final)
    {
        int pivo;

        // Escolhe o pivô
        pivo = Particiona(vetor, inicio, final);

        // Quick sort com a partição da esquerda e da direita
        QuickSort(vetor, inicio, pivo - 1);
        QuickSort(vetor, pivo + 1, final);
    }

    return;
}

/*Faz o particionamento do vetor no pivô
--- Recebe ---
(*int) vetor: ponteiro para vetor de inteiros
(int) inicio: index do inicio do vetor
(int) final: index do final do vetor
---- Retorna ---
(int) index do pivô
*/
int Particiona(int *vetor, int inicio, int final)
{
    int x, i, j, meio;

    // troca o valor do meio pelo do último elemento
    meio = (final + inicio) / 2;
    Swap(vetor, meio, final);

    // Faz o particionamento baseado no último elemento do vetor
    x = vetor[final];
    i = inicio;
    for (j = inicio; j < final; j++)
    {
        if (vetor[j] < x)
        {
            Swap(vetor, i, j);
            i++;
        }
    }
    Swap(vetor, i, j);

    return i;
}

/*Troca os valores dos elementos nas posições index1 e index2.
--- Recebe ---
(int*) vetor: ponteiro para vetor de inteiro
(int) index1: primeiro index
(int) index2: segundo index
*/
void Swap(int *vetor, int index1, int index2)
{
    int aux;
    aux = vetor[index1];
    vetor[index1] = vetor[index2];
    vetor[index2] = aux;
    return;
}
