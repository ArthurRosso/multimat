// C Program to multiply two matrix using pthreads without
// use of global variables
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>

// Each thread computes single element in the resultant matrix
void *mult(void *arg)
{
    int *data = (int *)arg;
    int c2 = data[0];
    int c1 = data[1];

    int i = 0, j = 0;
    int *res = (int *)malloc(c2 * sizeof(int));

    data += 2;
    for (j = 0; j < c2; j++)
    {
        int k = 0;
        for (i = 0; i < c1; i++)
        {
            k += data[i + (c1 * 2 * j)] * data[i + c1 + (c1 * 2 * j)];
        }

        res[j] = k;
    }

    free(arg);
    // Used to terminate a thread and the return value is passed as a pointer
    pthread_exit(res);
}

// Driver code
int main(int argc, char *argv[])
{
    int i, j, k, n;
    int N;
    int *A;
    int *B;
    int *C;
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
    A = (int *)malloc(N * N * sizeof(int));
    B = (int *)malloc(N * N * sizeof(int));
    C = (int *)malloc(N * N * sizeof(int));
    for (i = 0; i < N * N; i++)
    {
        A[i] = rand() % INT_MAX;
        B[i] = rand() % INT_MAX;
    }

    mean = 0.0;
    sigma = 0.0;
    timings = (double *)malloc(nb_exp * sizeof(double));

    // declaring array of threads of size r1*c2
    pthread_t *threads;
    threads = (pthread_t *)malloc(N * sizeof(pthread_t));


    for (n = 0; n < nb_exp; n++)
    {
        gettimeofday(&start, NULL);
        int count = 0;
        int *data = NULL;
        for (i = 0; i < N; i++)
        {

            // storing row and column elements in data
            data = (int *)malloc(((N + N) * N + 2) * sizeof(int)); // armazenar lin e col necessárias para calcular os elementos
            data[0] = N;
            data[1] = N;

            for (j = 0; j < N; j++)
            {

                for (k = 0; k < N; k++)
                {
                    data[k + 2 + (N * 2 * j)] = A[i + N * k];
                }

                for (k = 0; k < N; k++)
                {
                    data[k + N + 2 + (N * 2 * j)] = B[k + N * j];
                }
            }
            // creating threads
            pthread_create(&threads[count++], NULL, mult, (void *)(data));
        }
        count = 0;
        for (i = 0; i < N; i++)
        {
            pthread_join(threads[count++], NULL);
        }
        gettimeofday(&end, NULL);
        timings[n] = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
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

    printf("Duracao media dos produtos (%d experiencias) com pthreads:\n", nb_exp);
	printf("\t - ijk basico: %8.2lf sec. (desvio-p. : %8.2lf)\n", mean * 1e-6, sigma);

	free(A);
	free(B);
	free(C);
	free(timings);
	

    return 0;
}
