#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


#define num_steps 1000000000;


void aproximaPi_Sequencial();
void aproximaPi_Paralelo();


int main(){
    double inicio, fim;
    inicio = omp_get_wtime();
    aproximaPi_Sequencial();
    fim = omp_get_wtime();
    printf("Tempo sequencial: %.2f\n", fim - inicio);
    float media1 = (fim - inicio);


    inicio = omp_get_wtime();
    aproximaPi_Paralelo();
    fim = omp_get_wtime();
    printf("Tempo paralelo: %.2f\n", fim - inicio);
    float media2 = (fim - inicio);
    float speedup = media1/media2;
    printf("\nSpeedup: %.2f\t", speedup);
    float eficiencia = speedup/4;
    printf("Eficiencia: %.2f\n", eficiencia);
    return 0;
}


void aproximaPi_Sequencial(){
    double x, pi, sum = 0.0;
    int i;
    double step = 1.0/(double) num_steps;
    int num = num_steps;
    for (i=0; i < num; i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;
    printf("Valor de pi: %.20f\t", pi);
}
void aproximaPi_Paralelo(){
    double x, pi, sum = 0.0;
    int i;
    double step = 1.0/(double) num_steps;
    int num = num_steps;
    #pragma omp parallel private(x) num_threads(4)
    {
        #pragma omp for reduction(+:sum)
            for (i=0; i < num; i++){
                x = (i+0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }
    }
    pi = step * sum;
    printf("Valor de pi: %.20f\t", pi);
}


