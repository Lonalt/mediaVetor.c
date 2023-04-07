#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>


#define num_steps 2000009000
#define PI 3.14159265358979323846

void piSequencial();
void piPararelo1();
void piPararelo2();

int main()
{
    double start, end;
    start = omp_get_wtime();
    piSequencial();
    end = omp_get_wtime();
    printf("Tempo sequencial: %f\n", end - start);
    start = omp_get_wtime();
    piPararelo1();
    end = omp_get_wtime();
    printf("Tempo paralelo: %f\n", end - start);
    start = omp_get_wtime();
    piPararelo2();
    end = omp_get_wtime();
    printf("Tempo paralelo: %f\n", end - start);
    return 0;
}

void piSequencial()
{  
    double x, pi, sum = 0.0;
        int i;
        double step = 1.0/(double) num_steps;
        int num = num_steps;
        for (i=0; i < num; i++){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        pi = step * sum;
        printf("Pi: %.20f\t", pi);
        double pi2 = PI;
        double varia = pi - pi2;
        printf("Diferenca: %.20f\t", sqrt(varia*varia));
}

void piPararelo1()
{
    double pi, step;
    step = 1.0 / (double) num_steps;
    #pragma omp parallel num_threads(2)
    {
        double x, sum = 0.0;
        int i, id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for(i = id; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
            pi += sum * step;
    }
    printf("Pi: %.20f\t", pi);
    double pi2 = PI;
    double varia = pi - pi2;
    printf("Diferenca: %.20f\t", sqrt(varia*varia));
}

void piPararelo2(){
    double x, pi, sum = 0.0;
    int i;
    double step = 1.0/(double) num_steps;
    int num = num_steps;
    #pragma omp parallel private(x) num_threads(8)
    {
        #pragma omp for reduction(+:sum)
            for (i=0; i < num; i++){
                x = (i+0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }
    }
    pi = step * sum;
    printf("Pi: %.20f\t", pi);
    double pi2 = PI;
    double varia = pi - pi2;
    printf("Diferenca: %.20f\t", sqrt(varia*varia));
}











































