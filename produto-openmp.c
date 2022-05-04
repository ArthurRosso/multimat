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
    omp_set_dynamic(1);
    omp_set_num_threads(n);
    #pragma omp parallel shared(A, B, C) private(i, j, k)
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

int main(int argc, char *argv[])
{ // gcc produto-openmp.c -o produto-openmp -lm -fopenmp && ./produto-openmp 512
    int i, j, k;
    int N;
    double *A;
    double *B;
    double *C;
    double *timings;
    double mean, sigma;
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

    mean = 0.0;
    sigma = 0.0;
    timings = (double *)malloc(nb_exp * sizeof(double));

    for (j = 0; j < nb_exp; j++)
    {
        /* ijk babaca */
        gettimeofday(&start, NULL);
        ijk(N, C, A, B);
        gettimeofday(&end, NULL);
        timings[j] = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    }

    /* Estatisticas sobre os timings */
	/* Media */
		for (j = 0; j < nb_exp; j++)
		{
			mean += timings[j];
		}
		mean /= nb_exp;
	
	/* Desvio padrao */
    sigma = 0;
    for (j = 0; j < nb_exp; j++)
    {
        sigma += (mean - timings[j]) * (mean - timings[j]);
    }
    sigma = sqrt(sigma) * 1e-6 / nb_exp;

    printf("Duracao media dos produtos (%d experiencias) com openmp:\n", nb_exp);
	printf("\t - ijk basico: %8.2lf sec. (desvio-p. : %8.2lf)\n", mean * 1e-6, sigma);

	free(A);
	free(B);
	free(C);
	free(timings);

    return 0;
}