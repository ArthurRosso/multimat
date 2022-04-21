#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <omp.h>

void ijk(int n, double *C, double *A, double *B)
{
    int i, j, k;
    #pragma omp parallel shared(A, B, C) private(i, j, k)
    {
    #pragma omp for schedule(static)
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                for (k = 0; k < n; k++)
                {
                    C[j * n + i] += A[k * n + i] * B[j * n + k];
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{ // gcc main.c -o main -lm && ./main
    int i, j, k;
    int N;
    double *A;
    double *B;
    double *C;
    double *timings[8];
    double mean[8], sigma[8];
    int nb_exp = 8;
    struct timeval start;
    struct timeval end;

    if (argc != 2)
    {
        printf("%d nro param", argc);
        return -1;
    }
    N = atoi(argv[1]);

    srand(time(NULL));
    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    C = (double *)malloc(N * N * sizeof(double));
    for (i = 0; i < N * N; i++)
    {
        A[i] = ((double)rand() / INT_MAX);
        B[i] = ((double)rand() / INT_MAX);
    }

    for (i = 0; i < 8; i++)
    {
        mean[i] = 0.0;
        sigma[i] = 0.0;
        timings[i] = (double *)malloc(nb_exp * sizeof(double));
        /* timings[0][j] : tempo da execução j do algoritmo ijk
         * timings[1][j] : tempo da execução j do algoritmo ijk-buffer
         * timings[2][j] : tempo da execução j do algoritmo ikj-worst
         * timings[3][j] : tempo da execução j do algoritmo jki-best.
         */
    }

    for (j = 0; j < nb_exp; j++)
    {
        /* ijk babaca */
        gettimeofday(&start, NULL);
        ijk(N, C, A, B);
        gettimeofday(&end, NULL);
        timings[0][j] = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    }
    /* Estatisticas sobre os timings */
    /* Media */
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < nb_exp; j++)
        {
            mean[i] += timings[i][j];
        }
        mean[i] /= nb_exp;
    }
    /* Desvio padrao */
    for (i = 0; i < 8; i++)
    {
        sigma[i] = 0;
        for (j = 0; j < nb_exp; j++)
        {
            sigma[i] += (mean[i] - timings[i][j]) * (mean[i] - timings[i][j]);
        }
        sigma[i] = sqrt(sigma[i]) * 1e-6 / nb_exp;
    }

    printf("Duracao media dos produtos (%d experiencias):\n", nb_exp);
    printf("\t - ijk basico: %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[0] * 1e-6, sigma[0]);

    return 0;
}