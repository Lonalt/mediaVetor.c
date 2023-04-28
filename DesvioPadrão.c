#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define TAMANHO 100000000

// prototipos
int *gerarVetor(int tamanho);
double desvioPadraoSerial(int *vetor, int tamanho);
double desvioPadraoParalelo(int *vetor, int tamanho);

// funcao principal

int main() {
    int *vetor = gerarVetor(TAMANHO);
    double resultadoSerial = 0.0;
    double resultadoParalelo = 0.0;
    double tempoSerial = 0.0;
    double tempoParalelo = 0.0;
    clock_t inicio, fim;
    inicio = clock();
    resultadoSerial = desvioPadraoSerial(vetor, TAMANHO);
    fim = clock();
    tempoSerial = (double) (fim - inicio) / CLOCKS_PER_SEC;
    inicio = clock();
    resultadoParalelo = desvioPadraoParalelo(vetor, TAMANHO);
    fim = clock();
    tempoParalelo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    printf("\nDesvio padrao serial: %lf\t\t", resultadoSerial);
    printf("Tempo serial: %lf\n", tempoSerial);
    printf("Desvio padrao paralelo: %lf\t", resultadoParalelo);
    printf("Tempo paralelo: %lf\n\n", tempoParalelo);
    free(vetor);
    return 0;
}

// gera vetor de numeros aleatorios
int *gerarVetor(int tamanho) {
    int *vetor = (int *) malloc(sizeof(int) * tamanho);
    int i;
    srand(time(NULL));
    for (i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 100;
    }
    return vetor;
}

// calcula desvio padrao
double desvioPadraoSerial(int *vetor, int tamanho) {
    double media = 0.0;
    double desvioPadrao = 0.0;
    int i;
    for (i = 0; i < tamanho; i++) {
        media += vetor[i];
    }
    media /= tamanho;
    for (i = 0; i < tamanho; i++) {
        desvioPadrao += pow(vetor[i] - media, 2);
    }
    desvioPadrao /= tamanho;
    desvioPadrao = sqrt(desvioPadrao);
    return desvioPadrao;
}
double desvioPadraoParalelo(int *vetor, int tamanho) {
    double media = 0.0;
    double desvioPadrao = 0.0;
    int i;
    #pragma omp parallel for reduction(+:media)
    for (i = 0; i < tamanho; i++) {
        media += vetor[i];
    }
    media /= tamanho;
    #pragma omp parallel for reduction(+:desvioPadrao)
    for (i = 0; i < tamanho; i++) {
        desvioPadrao += pow(vetor[i] - media, 2);
    }
    desvioPadrao /= tamanho;
    desvioPadrao = sqrt(desvioPadrao);
    return desvioPadrao;
}





