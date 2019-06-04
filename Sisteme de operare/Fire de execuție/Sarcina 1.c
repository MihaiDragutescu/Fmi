#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void *hello(void *v)//functia de calculare a inversului
{
   int i;
   char *sir=(char *)v;
   char *invers=(char *)malloc(strlen(sir));

   for(i=strlen(sir)-1;i>=0;i--)
   invers[strlen(sir)-i-1]=sir[i];

   return invers;
}

int main(int argc,char *argv[])
{
   char *rezultat;
   pthread_t thr;

   if(pthread_create(&thr,NULL,hello,argv[1]))//verificam daca avem eroare la crearea firului de executie
   {
      perror(NULL);
      return errno;
   }

   if(pthread_join(thr,(void**)&rezultat))//verificam daca avem eroare la asteptarea finalizarii firului de executie
   {
      perror(NULL);
      return errno;
   }

   printf("%s\n",rezultat);
   return 0;
}
