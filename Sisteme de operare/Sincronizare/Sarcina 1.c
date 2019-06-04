#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_RESOURCES 5

int available_resources=MAX_RESOURCES;
pthread_mutex_t mutex;//se foloseste mutex-ul pentru asigurarea accesului exclusiv intr-o zona critica(zona in care are voie un singur proces sau thread)

int decrease_count(int count)
{
   if(available_resources<count)
   {
      return -1;
   }
   else
   {
      available_resources-=count;
   }

   return 0;
}

int increase_count(int count)
{
    available_resources+=count;

    return 0;
}

void* resource(void *cnt)
{
  
   int* count=(int*)malloc(sizeof(int));
   count=(int*)cnt; 

   printf("Thread wants %d resources\n",*count);
   pthread_mutex_lock(&mutex);//thread detine dreptul exclusiv de executie asupra zonei critice până ce decide să renunte la acest drept

   if(decrease_count(*count)==0)
   {
       pthread_mutex_unlock(&mutex);
       printf("Got %d resources, %d remaining resources\n",*count, available_resources);
       pthread_mutex_lock(&mutex);
       increase_count(*count);
       printf("Released %d resources, %d remaining resources\n",*count, available_resources);
       pthread_mutex_unlock(&mutex);
       
   }
   else
   {
      pthread_mutex_unlock(&mutex);
      printf("No resources available\n");
   }  
}

int main(int arg, char **argv)
{
    int nr_threads=atoi(argv[1]);
    pthread_t thread[nr_threads];

    if(pthread_mutex_init(&mutex,NULL))//verificam daca avem eroare la crearea obiectului de timp mutex
    {
        perror(NULL);
        return errno;
    }

    int *count_array=(int*)malloc(sizeof(int)*nr_threads);//vector de resurse
    int i;

    for(i=0;i<nr_threads;i++)
    {
        count_array[i]=rand()%(MAX_RESOURCES+2);
        printf("%d ",count_array[i]);
    }
    printf("\n");

    for(i=0;i<nr_threads;i++)
    {
        pthread_create(&thread[i],NULL,resource,&count_array[i]);
    }
    
    void *result;
    for(i=0;i<nr_threads;i++)
    {
      if(pthread_join(thread[i],&result))
      {
        perror(NULL);
        return errno;
      }
    }

    pthread_mutex_destroy(&mutex);//eliberam resursele ocupate de mutex
    free(count_array);

    return 0;
}
