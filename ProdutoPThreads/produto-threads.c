#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#include "dclock.h"

/*
 *
 * Compila��o:
 *  gcc -o whatever produto-threads.c -lpthread
 */

#define NBTHREADS 4
/* Armazenamento por colunas. Para todas as matrizes:
 *    A(i,j) <==> A[j*n + i]
 * Presuposto: todas as matrizes s�o incializadas com o valor 0.
 */

/* Uma vari�vel global */
int matrix_size;

double *A;
double *B;
double *C;

/* Fun��o sequencial que calcula uma linha da matriz resultado. O n�mero da linha ('i') �
 * passado em argumento.
 * Esta fun��o ser� executada por uma thread.
 */

void *compute_j_k(void *arg)
{
   int i = (int)arg;
   int j, k;
   pthread_t my_th_id;
   my_th_id = pthread_self();
   printf("Thread %d processing line number %d.\n", (int)my_th_id, i);
   for (j = 0; j < matrix_size; j++)
   {
      for (k = 0; k < matrix_size; k++)
         C[j * matrix_size + i] += A[k * matrix_size + i] * B[j * matrix_size + k];
   }
}

/* A versao ijk b�sica */
void ijk(int n)
{
   int i, j, k;
   int th_id;
   int th_arg;
   pthread_t *threads;
   int *retornos;

   matrix_size = n;

   /* Aloca um vetor de NTHREADS threads a serem criados. */
   threads = (pthread_t *)malloc(NBTHREADS * sizeof(pthread_t));
   /* Aloca um vetor de NTHREADS c�digos de retorno. */
   retornos = (int *)malloc(NBTHREADS * sizeof(int));

   for (i = 0; i < n; i += NBTHREADS)
   {
      /* A vers�o sequencial rodava:
      for (j=0 ; j<n ; j++) {
         for (k=0 ; k<n ; k++)
            C[j*n+i] += A[k*n+i]*B[j*n+k] ;
      }
      */
      /* Agora cada thread calcula uma linha i da matriz C */
      for (th_id = 0; th_id < NBTHREADS; th_id++)
      {
         th_arg = i + th_id;
         retornos[th_id] = pthread_create(&(threads[th_id]), NULL, compute_j_k, (void *)th_arg);
      }
      /* Espera at� todas as threads terem terminado. */
      for (th_id = 0; th_id < NBTHREADS; th_id++)
         pthread_join(threads[th_id], NULL);

      /*... e passa ao pr�ximo lote de itera��es de i.
       * Obs: s� funciona se n � um m�ltiplo de NBTHREADS
       */
   }
   printf("All computations ok.\n");
}

int main(int argc, char *argv[])
{
   int i, j, k;
   int N = 1000;
   double time1, time2;
   double *timings;
   double mean, sigma;
   int nb_exp, exp_num;
   FILE *out_gnuplot;

   if (argc != 4)
   {
      printf("Uso: %s <matrix-size> <nb-experiments> <#experimento> (see run.sh)\n", argv[0]);
      exit(-1);
   }
   N = atoi(argv[1]);
   nb_exp = atoi(argv[2]);
   exp_num = atoi(argv[3]);

   A = (double *)calloc(N * N, sizeof(double));
   B = (double *)calloc(N * N, sizeof(double));
   C = (double *)calloc(N * N, sizeof(double));

   time1 = DCLOCK();
   /* Inicializa��o das matrizes */
   srand(time1);
   for (i = 0; i < N * N; i++)
   {
      A[i] = ((double)rand() / INT_MAX);
      B[i] = ((double)rand() / INT_MAX);
   }
   mean = 0;
   sigma = 0;
   timings = (double *)malloc(nb_exp * sizeof(double)); /* timings[j] : tempo da execu�ao j do algoritmo ijk */

   /***********************************/
   /* Aqui se faz tudo... */
   /***********************************/

   /* Roda 'nb_exp' vezes o produto matricial */
   for (j = 0; j < nb_exp; j++)
   {
      /* ijk */
      time1 = DCLOCK();
      ijk(N);
      time2 = DCLOCK();
      timings[j] = time2 - time1;
   }
   /***********************************/
   /* Estat�sticas e impress�o na tela */
   /* Estatisticas sobre os timings */
   /* Media */
   for (j = 0; j < nb_exp; j++)
      mean += timings[j];
   mean /= nb_exp;
   /* Desvio padrao */
   sigma = 0;
   for (j = 0; j < nb_exp; j++)
      sigma += (mean - timings[j]) * (mean - timings[j]);
   sigma = sqrt(sigma) * 1E-6 / nb_exp;

   printf("Duracao media dos produtos (%d experiencias):\n", nb_exp);
   printf("\t - ijk basico: %8.2lf sec. (desvio-p. : %8.2lf)\n",
          mean * 1E-6, sigma);
   out_gnuplot = fopen("data_gnuplot.txt", "w");
   fprintf(out_gnuplot, "%d, %d, ", exp_num, N);
   fprintf(out_gnuplot, "%8.2lf,", mean * 1E-6);
   fclose(out_gnuplot);
   return 0;
}
