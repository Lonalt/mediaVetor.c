#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <omp.h>

#define VetMax 500000000;

double *geraVetor(int tam);
void desalocaVetor(double *vetor);
void somaVetor(double *vetor, int tam);
void somaVetorParalelo(double *vetor, int tam);

int main(){
    setlocale(LC_ALL, "Portuguese");
    double tam = VetMax;
    system("cls");
    double *vetor = geraVetor(tam);

    double inicio = omp_get_wtime();
    somaVetor(vetor, tam);
    double fim = omp_get_wtime();
    double tempoSeq = fim - inicio;
    printf("Tempo de execucao: %.2f\n\n", fim - inicio);


    inicio = omp_get_wtime();
    somaVetorParalelo(vetor, tam);
    fim = omp_get_wtime();
    double tempoPar = fim - inicio;
    printf("Tempo de execucao: %.2f\n\n", fim - inicio);

    float speedup = tempoSeq / tempoPar;
    printf("\nSpeedup: %.2f\n", speedup);
    printf("Eficiencia: %.2f\n", speedup / 8);

    desalocaVetor(vetor);
    return 0;
}

// Função que gera um vetor de números aleatórios
double *geraVetor(int tam){
    double *vetor = (double *) malloc(tam * sizeof(double));
    int i;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < tam; i++){
        vetor[i] = rand() % 100000;
    }
    printf("\nVetor gerado com sucesso!\n\n");
    return vetor;
}

// Função que desaloca um vetor
void desalocaVetor(double *vetor){
    free(vetor);
}

// Função sequencial que calcula a soma dos elementos de um vetor e a media
void somaVetor(double *vetor, int tam){
    double soma = 0;
    int i;
    for(i = 0; i < tam; i++){
        soma += vetor[i];
    }
    double media = soma / tam;
    printf("Valores de soma sequencial:\n");
    printf("Soma: %.2f\t\t",soma);
    printf("Media: %.2f\n",media);
}
// Função paralela que calcula a soma dos elementos de um vetor e a media
void somaVetorParalelo(double *vetor, int tam){
    double soma = 0;
    int i;
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for reduction(+:soma)
        for(i = 0; i < tam; i++){
            soma += vetor[i];
        }
    }
    double media = soma / tam;
    printf("Valores de soma pararela:\n");
    printf("Soma: %.2f\t\t",soma);
    printf("Media: %.2f\n",media);
}









