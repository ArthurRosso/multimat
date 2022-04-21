#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

int N;
int NT;
double *A;
double *B;
double *C;
int step_i = 0;

void *compute_j_k(void *arg)
{
    int i = (*(int*)arg);
    int j, k;
    for (j = 0; j < N; j++)
    {
        for (k = 0; k < N; k++)
        {
            C[j * N + i] += A[k * N + i] * B[j * N + k];
        }
    }
}

/* A versao ijk básica */
void ijk()
{
    int i, j, k;
    int th_id;
    int th_arg;
    pthread_t *threads;
    int *retornos;
    threads = (pthread_t *)malloc(NT * sizeof(pthread_t));
    retornos = (int *)malloc(NT * sizeof(int));

    for (i = 0; i < N; i += NT)
    {
        for (th_id = 0; th_id < NT; th_id++)
        {
            th_arg = i + th_id;
            retornos[th_id] = pthread_create(&(threads[th_id]), NULL, compute_j_k, (void *)th_arg);
        }
        for (th_id = 0; th_id < NT; th_id++)
        {
            pthread_join(threads[th_id], NULL);
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j, k;
    double *timings[8];
    double mean[8], sigma[8];
    int nb_exp = 8;
    struct timeval start;
    struct timeval end;

    if (argc != 3)
    {
        printf("%d nro param", argc);
        return -1;
    }
    N = atoi(argv[1]);
    NT = atoi(argv[2]);

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
    }

    // declaring our threads
    pthread_t threads[NT];

    for (j = 0; j < nb_exp; j++)
    {
        /* ijk babaca */
        gettimeofday(&start, NULL);
        ijk();
        gettimeofday(&end, NULL);
        timings[0][j] = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    }

    /* Estatisticas sobre os timings */
    /* Media */
    for (j = 0; j < nb_exp; j++)
    {
        mean[0] += timings[0][j];
    }
    mean[0] /= nb_exp;
    /* Desvio padrao */
    sigma[0] = 0;
    for (j = 0; j < nb_exp; j++)
    {
        sigma[0] += (mean[0] - timings[0][j]) * (mean[0] - timings[0][j]);
    }
    sigma[0] = sqrt(sigma[0]) * 1e-6 / nb_exp;

    printf("Duracao media dos produtos (%d experiencias):\n", nb_exp);
    printf("\t - ijk basico: %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[0] * 1e-6, sigma[0]);

    return 0;
}
