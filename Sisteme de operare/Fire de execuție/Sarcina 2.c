#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define nr_threads 4
#define a 2
#define b 3
#define c 2

int mat_1[a][b]={{1, 2, 3},
                 {4, 5, 6}};

int mat_2[b][c]={{7, 8},
                 {9, 10},
                 {11,12}};

int mat_rez[a][c];

struct element
{
   int i,j;
};

int pozitie=-1;
struct element de_generat()
{
   struct element e={pozitie/c,pozitie%c};
   return e;
}

void *hello(void *v)
{
   pozitie++;
   struct element e=de_generat();

   for(int k=0;k<b;k++)
      mat_rez[e.i][e.j]+=mat_1[e.i][k]*mat_2[k][e.j];

   return NULL;   
}

int main()
{
   pthread_t thread[nr_threads];
   int t[nr_threads];
   
   for(int i=0;i<nr_threads;i++)
   {
      t[i]=i;
      pthread_create(&thread[i],NULL,hello,(void*)(t+i));
   }
   
   for(int i=0;i<nr_threads;i++)
      pthread_join(thread[i],NULL);

   for(int i=0;i<a;i++)
   {
      for(int j=0;j<c;j++)
         printf("%d ",mat_rez[i][j]);
      printf("\n");
   }
   return 0;
}
