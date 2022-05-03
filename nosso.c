// C Program to multiply two matrix using pthreads without
// use of global variables
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 4

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
int main()
{

    int matA[MAX][MAX];
    int matB[MAX][MAX];

    int r1 = MAX, c1 = MAX, r2 = MAX, c2 = MAX, i, j, k;

    // Generating random values in matA
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            matA[i][j] = rand() % 10;

    // Generating random values in matB
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            matB[i][j] = rand() % 10;

    printf("Displaying matA\n");
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
            printf("%d ", matA[i][j]);
        printf("\n");
    }

    printf("\nDisplaying matB\n");
    for (i = 0; i < r2; i++)
    {
        for (j = 0; j < c2; j++)
            printf("%d ", matB[i][j]);
        printf("\n");
    }

    int max = r1 * c2;

    // declaring array of threads of size r1*c2
    pthread_t *threads;
    threads = (pthread_t *)malloc(r1 * sizeof(pthread_t));

    int count = 0;
    int *data = NULL;
    for (i = 0; i < r1; i++)
    {

        // storing row and column elements in data
        data = (int *)malloc(((c1 + r2) * c2 + 2) * sizeof(int)); // armazenar lin e col necessárias para calcular os elementos
        data[0] = c2;
        data[1] = c1;

        for (j = 0; j < c2; j++)
        {

            for (k = 0; k < c1; k++)
                data[k + 2 + (c1 * 2 * j)] = matA[i][k];

            for (k = 0; k < r2; k++)
                data[k + c1 + 2 + (c1 * 2 * j)] = matB[k][j];
        }
        // creating threads
        pthread_create(&threads[count++], NULL, mult, (void *)(data));
    }
    count = 0;
    for (i = 0; i < r1; i++)
    {
        int *res;
        pthread_join(threads[count++], (void **)&res);
        for (j = 0; j < c2; j++)
        {
            printf("%d ", res[j]);
        }
        free(res);
        printf("\n");
    }
    // TODO: valgrind
    return 0;
}
