Produto matricial e Threads Posix

I. Observações iniciais
------------------------

Todas as medições de tempo são efetuadas por meio de
DLCOCK(), implementada em dclock.c e dclock.h. É ESSENCIAL atualizar em
dclock.c o valor da frequência de relógio do processador usado (cf. a linha
'#define CLOCK_FREQ 2900'). Para obtê-la, pode-se usar 'cat /proc/cpuinfo'.


O código fonte principal está em 'produto-threads.c' (e 'produto.c' para a versão sem threads).

O arquivo 'Makefile' serve para compilar os códigos. Digitar 'make', ou 'make all', ou ainda
'make produto-threads' compila os arquivos apropriados para criar os executáveis.

II. Pontos a exercitar
----------------------


A linha '#define NBTHREADS 4' define o número de threads a executar (que, em
função da programação simplificada deste exemplo, precisa dividir exatamente
o tamanho da matriz. Usar 4, 5 ou 10 threads como N=500 vai funcionar, mas não
usar 7 threads com N=500 ou 4 threads com N=501. É interessante estudar o que
aconteceria nestes casos, e como resolver estes problemas.) 
Experimentar com o número de threads, quando se fixa o tamanho da matriz.  
Experimentar com um número fixo de threads, quando o tamanho da matriz aumenta.  
Experimentar o tempo de execução sequencial (NBTHREADS=1) e relação ao tempo de execução com
threads.  
Comparar o tempo de execução do programa "Puramente sequencial" (produto.c) com o tempo de execução do programa com threads, com NBTHREADS=1.

("Experimentar" significa executar o programar e verificar o tempo de execução. Pode-se produzir 
gráficos, por exemplo..).

-------------------------------------------------------------------------------------------
Na versão com threads, 4 variávais globais foram declaradas: 
int matrix_size;
double* A ;
double* B ;
double* C ;

Teria alternativas a estas declarações globais? 
Estamos tratando de variáveis globais, e portanto compartilhadas entre as threads. 
Existem riscos de acesssos concorrentes? 

-------------------------------------------------------------------------------------------
No fim do laço for (i=0 ; i<n ; i+= NBTHREADS) { do procedimento 'ijk', existe uma série de 
chamadas a 'pthread_join'. Qual é o efeito destas? O que acontece sem estas chamadas?

-------------------------------------------------------------------------------------------
As threads são introduzidas no programa para distribuir as iterações 'i' do laço principal
do procedimento ijk(). Teria outras abordagens para ter várias threads compartilhando os 
cálculos? Elas poderiam introduzir riscos de acessos concorrentes?

-------------------------------------------------------------------------------------------
Outras variações da implementação do produto matricial, mais eficientes, vêm no arquivo produto.c. 
Propor versões paralelas, com threads Posix, da mais eficiente sequencialmente.
Medir o desempenho.  Existe conflito entre a localidade (ou seja, o uso eficiente de acessos 
contíguos na memória, tais que caibam numa página) e o uso de threads?
