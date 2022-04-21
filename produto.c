#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <limits.h>

/* Armazenamento por colunas. Para todas as matrizes:
 *    A(i,j) <==> A[j*n + i]
 * Presuposto: todas as matrizes são incializadas com o valor 0.
 */

/* A versao ijk básica */
void ijk(int n, double *C, double *A, double *B)
{
   int i, j, k;
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

/* A versao ijk menos boba - o compilador deveria saber fazer essa otimizacao
 * sozinho... Eh esta versão que vou considerar uma vez que nas outras eu
 * uso variaveis temporarias.
 */
void ijk_buffer(int n, double *C, double *A, double *B)
{
   int i, j, k;
   double tmp;
   double *ptr_Bjn;
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         tmp = 0;
         ptr_Bjn = &(B[j * n]);
         for (k = 0; k < n; k++)
         {
            /* v1. tmp += A[k*n+i]*B[j*n+k] ; */
            tmp += A[k * n + i] * (*(ptr_Bjn + k));
         }
         C[j * n + i] = tmp;
      }
   }
}

/* A mesma com unroll */
void ijk_buffer_unroll(int n, double *C, double *A, double *B)
{
   int i, j, k;
   double tmp;
   double *ptr_Bjn;
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         tmp = 0;
         ptr_Bjn = &(B[j * n]);
         for (k = 0; k < n; k += 8)
         {
            /* v1. tmp += A[k*n+i]*B[j*n+k] ; */
            tmp += A[k * n + i] * (*(ptr_Bjn + k));
            tmp += A[(k + 1) * n + i] * (*(ptr_Bjn + k + 1));
            tmp += A[(k + 2) * n + i] * (*(ptr_Bjn + k + 2));
            tmp += A[(k + 3) * n + i] * (*(ptr_Bjn + k + 3));
            tmp += A[(k + 4) * n + i] * (*(ptr_Bjn + k + 4));
            tmp += A[(k + 5) * n + i] * (*(ptr_Bjn + k + 5));
            tmp += A[(k + 6) * n + i] * (*(ptr_Bjn + k + 6));
            tmp += A[(k + 7) * n + i] * (*(ptr_Bjn + k + 7));
         }
         C[j * n + i] = tmp;
      }
   }
}

/* A versao jki. Eu disse que era a melhor... Ela tem uma cara boa :o)
 */
void jki_best(int n, double *C, double *A, double *B)
{
   int i, j, k;
   double Bkj;
   double *ptr_Akn;
   double *ptr_Cjn;
   for (j = 0; j < n; j++)
   {
      ptr_Cjn = &(C[j * n]);
      for (k = 0; k < n; k++)
      {
         Bkj = B[j * n + k];
         ptr_Akn = &(A[k * n]);
         for (i = 0; i < n; i++)
         {
            /* v1. C[j*n+i] += A[k*n+i]*Bkj ; */
            *(ptr_Cjn + i) += *(ptr_Akn + i) * Bkj;
         }
      }
   }
}

/* A versao jki. Eu disse que era a melhor... Ela tem uma cara boa :o)
 *  On deroule la boucle interieure...Juste pour rigoler.
 */
void jki_best_unroll(int n, double *C, double *A, double *B)
{
   int i, j, k;
   double Bkj;
   double *ptr_Akn;
   double *ptr_Cjn;
   for (j = 0; j < n; j++)
   {
      ptr_Cjn = &(C[j * n]);
      for (k = 0; k < n; k++)
      {
         Bkj = B[j * n + k];
         ptr_Akn = &(A[k * n]);
         for (i = 0; i < n; i += 8)
         {
            /* v1. C[j*n+i] += A[k*n+i]*Bkj ; */
            *(ptr_Cjn + i) += *(ptr_Akn + i) * Bkj;
            *(ptr_Cjn + i + 1) += *(ptr_Akn + i + 1) * Bkj;
            *(ptr_Cjn + i + 2) += *(ptr_Akn + i + 2) * Bkj;
            *(ptr_Cjn + i + 3) += *(ptr_Akn + i + 3) * Bkj;
            *(ptr_Cjn + i + 4) += *(ptr_Akn + i + 4) * Bkj;
            *(ptr_Cjn + i + 5) += *(ptr_Akn + i + 5) * Bkj;
            *(ptr_Cjn + i + 6) += *(ptr_Akn + i + 6) * Bkj;
            *(ptr_Cjn + i + 7) += *(ptr_Akn + i + 7) * Bkj;
         }
      }
   }
}

/* A versao jki. Com blocos
 */
#define BLOCK 64
void jki_blocos(int n, double *C, double *A, double *B)
{
   int i, j, k, I, J, K;
   double Bkj;
   double *ptr_Akn;
   double *ptr_Cjn;
   for (J = 0; J < n; J += BLOCK)
   {
      for (K = 0; K < n; K += BLOCK)
      {
         for (I = 0; I < n; I += BLOCK)
         {
            for (j = J; j < J + BLOCK - 1 && j < n; j++)
            {
               ptr_Cjn = &(C[j * n]);
               for (k = K; k < K + BLOCK - 1 && k < n; k++)
               {
                  Bkj = B[j * n + k];
                  ptr_Akn = &(A[k * n]);
                  for (i = I; i < I + BLOCK - 1 && i < n; i++)
                  {
                     *(ptr_Cjn + i) += *(ptr_Akn + i) * Bkj;
                  }
               }
            }
         }
      }
   }
}

void jki_blocos_unroll(int n, double *C, double *A, double *B)
{
   int i, j, k, I, J, K;
   double Bkj;
   double *ptr_Akn;
   double *ptr_Cjn;
   for (J = 0; J < n; J += BLOCK)
   {
      for (K = 0; K < n; K += BLOCK)
      {
         for (I = 0; I < n; I += BLOCK)
         {
            for (j = J; j < J + BLOCK - 1 && j < n; j++)
            {
               ptr_Cjn = &(C[j * n]);
               for (k = K; k < K + BLOCK - 1 && k < n; k++)
               {
                  Bkj = B[j * n + k];
                  ptr_Akn = &(A[k * n]);
                  for (i = I; i < I + BLOCK - 1 && i < n; i += 8)
                  {
                     *(ptr_Cjn + i) += *(ptr_Akn + i) * Bkj;
                     /* v1. C[j*n+i] += A[k*n+i]*Bkj ; */
                     *(ptr_Cjn + i + 1) += *(ptr_Akn + i + 1) * Bkj;
                     *(ptr_Cjn + i + 2) += *(ptr_Akn + i + 2) * Bkj;
                     *(ptr_Cjn + i + 3) += *(ptr_Akn + i + 3) * Bkj;
                     *(ptr_Cjn + i + 4) += *(ptr_Akn + i + 4) * Bkj;
                     *(ptr_Cjn + i + 5) += *(ptr_Akn + i + 5) * Bkj;
                     *(ptr_Cjn + i + 6) += *(ptr_Akn + i + 6) * Bkj;
                     *(ptr_Cjn + i + 7) += *(ptr_Akn + i + 7) * Bkj;
                  }
               }
            }
         }
      }
   }
}

/* A versao ikj. Deve ser uma das 2 piores, junto com a kij. */
void ikj_worst(int n, double *C, double *A, double *B)
{
   int i, j, k;
   double tmp;
   for (i = 0; i < n; i++)
   {
      for (k = 0; k < n; k++)
      {
         tmp = A[k * n + i];
         for (j = 0; j < n; j++)
         {
            C[j * n + i] += tmp * B[j * n + k];
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
   double start;
   double end;

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
      start = DCLOCK();
      ijk(N, C, A, B);
      end = DCLOCK();
      timings[0][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* ijk otimizado */
      start = DCLOCK();
      ijk_buffer(N, C, A, B);
      end = DCLOCK();
      timings[1][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* ijk buffer unrolled  */
      start = DCLOCK();
      ijk_buffer_unroll(N, C, A, B);
      end = DCLOCK();
      timings[2][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* jki_best */
      start = DCLOCK();
      jki_best(N, C, A, B);
      end = DCLOCK();
      timings[3][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* jki_best_unroll(N, C, A, B) ; */
      start = DCLOCK();
      jki_best_unroll(N, C, A, B);
      end = DCLOCK();
      timings[4][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* jki_blocos(N, C, A, B) ; */
      start = DCLOCK();
      jki_blocos(N, C, A, B);
      end = DCLOCK();
      timings[5][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* ikj_blocos_unroll(N, C, A, B) ; */
      start = DCLOCK();
      jki_blocos_unroll(N, C, A, B);
      end = DCLOCK();
      timings[6][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
      /* ikj_worst(N, C, A, B) ; */
      start = DCLOCK();
      ikj_worst(N, C, A, B);
      end = DCLOCK();
      timings[7][j] = end-start;
      for (i = 0; i < N * N; i++)
         C[i] = 0;
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
   printf("\t - ijk buffer: %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[1] * 1e-6, sigma[1]);
   printf("\t - ijk buffer unroll : %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[2] * 1e-6, sigma[2]);
   printf("\t - jki best  : %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[3] * 1e-6, sigma[3]);
   printf("\t - jki best unroll  : %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[4] * 1e-6, sigma[4]);
   printf("\t - jki blocos : %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[5] * 1e-6, sigma[5]);
   printf("\t - jki blocos unroll : %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[6] * 1e-6, sigma[6]);
   printf("\t - ikj worst : %8.2lf sec. (desvio-p. : %8.2lf)\n", mean[7] * 1e-6, sigma[7]);

   return 0;
}