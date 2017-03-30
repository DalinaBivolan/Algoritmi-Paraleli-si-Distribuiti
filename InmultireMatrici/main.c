#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NRA 5            //numarul de linii din matricea A
#define NCA 4           //numarul de coloane sin matricea A si numarul de linii din matricea B
#define NCB 7           //numarul de coloane din matricea B


int a [NRA][NCA];
int b [NCA][NCB];
int c [NRA][NCB];

struct v {
   int i; //linie
   int j; //coloana
   int tID; //id-ul firului
};

void *multiply(void *param); //thread-ul

int main(int argc, char *argv[]) {

   int i,j; //count = 0;
   srand(time(NULL));

   printf("Initializare matrici...\n");
   //initializare matrice A
   for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++){
      a[i][j]=rand()%10;
      //printf("%d  ",a[i][j]);
    }
    //initializare martice B
    for (i=0; i<NCA; i++)
        for (j=0; j<NCB; j++){
            b[i][j]=rand()%10+10;
            //printf("%d  ",b[i][j]);
        }
    //initializare matrice rezultat C
    for (i=0; i<NRA; i++)
        for (j=0; j<NCB; j++)
            c[i][j]= 0;
   printf("----------------------------------------------------------------------------\n");
   for(i = 0; i < NRA; i++) {
      for(j = 0; j < NCB; j++) {
         //fiecare fir ia o linie si o coloana
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         //cream firul care primeste data ca parametru
         pthread_t tid;       //Thread ID
         data->tID=(int)tid;
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
        //creare thread
         pthread_create(&tid,&attr,multiply,data);

         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         //count++;
      }
   }
    //printf("Count=%d\n",count);
   //afisare matrice rezultat C
   printf("Matricea rezultat C: \n");
   for(i = 0; i < NRA; i++) {
      for(j = 0; j < NCB; j++) {
         printf("%d ", c[i][j]);
      }
      printf("\n");
   }
   return 0;
}

//The thread will begin control in this function
void *multiply(void *param) {
   struct v *data = param;
   int n, sum = 0; //contorul si suma

   //inmulteste linie cu coloana
   printf("Firul %d inmulteste linia %d cu coloana %d. \n",data->tID,data->i,data->j);
   for(n = 0; n< NCA; n++){
      sum += a[data->i][n] * b[n][data->j];
   }

   c[data->i][data->j] = sum;

   pthread_exit(0);
}

