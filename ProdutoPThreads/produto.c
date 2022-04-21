#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include "dclock.h"

/* Armazenamento por colunas. Para todas as matrizes:
 *    A(i,j) <==> A[j*n + i]
 * Presuposto: todas as matrizes s�o incializadas com o valor 0.
 */

/* A versao ijk b�sica */
void ijk(int n, double *C, double *A, double *B)
{
   int i, j, k;
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         for (k = 0; k < n; k++)
            C[j * n + i] += A[k * n + i] * B[j * n + k];
      }
   }
}

int main(int argc, char *argv[])
{
   int i, j, k;
   int N = 1000;
   double *A;
   double *B;
   double *C;
   double time1, time2;
   double *timings[8];
   double mean[8], sigma[8];
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
   for (i = 0; i < 8; i++)
   {
      mean[i] = 0;
      sigma[i] = 0;
      timings[i] = (double *)malloc(nb_exp * sizeof(double));
      /* timings[0][j] : tempo da execu�ao j do algoritmo ijk
       * timings[1][j] : tempo da execu�ao j do algoritmo ijk-buffer
       * timings[2][j] : tempo da execu�ao j do algoritmo ikj-worst
       * timings[3][j] : tempo da execu�ao j do algoritmo jki-best.
       */
   }

   /***********************************/
   /* Aqui se faz tudo... */
   /***********************************/

   /* Roda 'nb_exp' vezes o produto matricial */
   for (j = 0; j < nb_exp; j++)
   {
      /* ijk */
      time1 = DCLOCK();
      ijk(N, C, A, B);
      time2 = DCLOCK();
      timings[0][j] = time2 - time1;
   }
   /***********************************/
   /* Estat�sticas e impress�o na tela */
   /* Estatisticas sobre os timings */
   /* Media */
   for (j = 0; j < nb_exp; j++)
      mean[0] += timings[0][j];
   mean[0] /= nb_exp;
   /* Desvio padrao */
   sigma[0] = 0;
   for (j = 0; j < nb_exp; j++)
      sigma[0] += (mean[0] - timings[0][j]) * (mean[0] - timings[0][j]);
   sigma[0] = sqrt(sigma[0]) * 1E-6 / nb_exp;

   printf("Duracao media dos produtos (%d experiencias):\n", nb_exp);
   printf("\t - ijk basico: %8.2lf sec. (desvio-p. : %8.2lf)\n",
          mean[0] * 1E-6, sigma[0]);
   out_gnuplot = fopen("data_gnuplot.txt", "w");
   fprintf(out_gnuplot, "%d, %d, ", exp_num, N);
   fprintf(out_gnuplot, "%8.2lf,", mean[0] * 1E-6);
   fclose(out_gnuplot);
   return 0;
}
