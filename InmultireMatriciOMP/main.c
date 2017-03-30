#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NRA 70                 //numarul de linii din matricea A
#define NCA 30                 //numarul de coloane sin matricea A si numarul de linii din matricea B
#define NCB 7                  //numarul de coloane din matricea B

int main (int argc, char *argv[])
{
int	tid, nthreads, i, j, k, chunk;
int	a[NRA][NCA],           //matricea A
    b[NCA][NCB],           //matricea B
    c[NRA][NCB];           //matricea C=A*B

chunk = 10;
srand(time(NULL));

#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Inmultirea matricilor cu %d fire de executie\n",nthreads);
    printf("Initializare matrici...\n");
    }
  //Initializare matrici
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++){
      a[i][j]=rand()%10;
      //printf("%d  ",a[i][j]);
    }
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++){
      b[i][j]=rand()%10+10;
      //printf("%d  ",b[i][j]);
    }
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  printf("Firul %d a inceput inmultirea matricilor...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    {
    printf("Firul=%d a facut linia=%d\n",tid,i);
    for(j=0; j<NCB; j++)
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   //sfarsitul regiunii paralele

printf("------------------------------------------------------\n");
printf("Matricea rezultat C:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++)
    printf("%d   ", c[i][j]);
  printf("\n");
  }
printf("------------------------------------------------------\n");

return 0;
}

