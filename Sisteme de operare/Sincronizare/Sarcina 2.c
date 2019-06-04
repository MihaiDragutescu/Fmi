#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

int nr_threads;
sem_t sem;
pthread_mutex_t mutex;
int count;

int barrier_point()
{
    
    pthread_mutex_lock(&mutex);
    count++;
    int local=count;
    pthread_mutex_unlock(&mutex);
    
    if(local==nr_threads)
    {
        int i;
        for(i=0;i<nr_threads;i++)
        {
            if(sem_post(&sem))//verificam daca avem eroare la incrementarea(deschiderea) semaforului pointat de sem
            {
                perror(NULL);
                return errno;
            }
        }   
    }  
}

void* tfun(void *arg)
{

    int* tid=(int*)arg;//numarul threadului pornit
    printf("%d reached the barrier\n",*tid);
    barrier_point();
    if(sem_wait(&sem))//verificam daca avem eroare la decrementarea(inchiderea) semaforului pointat de sem 
    {
        perror(NULL);
    }

    printf("%d passed the barrier\n",*tid);
    return NULL;
}

int main(int argc,char** argv)
{
    nr_threads=atoi(argv[1]);
    pthread_t thread[nr_threads];

    if(pthread_mutex_init(&mutex,NULL))
    {
        perror(NULL);
        return errno;
    }

    if(sem_init(&sem,0,0))//verificam daca avem eroare la initializarea semaforului
    {
        perror(NULL);
        return errno;
    }

    int i;
    void *result;
    int count_array[nr_threads];

    for(i=0;i<nr_threads;i++)
    {
        count_array[i]=i;
    }

    for(i=0;i<nr_threads;i++)
    {
        pthread_create(&thread[i],NULL,tfun,&count_array[i]);
    }

    for(i=0;i<nr_threads;i++)
    {
       if(pthread_join(thread[i],&result))
       {
          perror(NULL);
          return errno;
      }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
   
    return 0;
}
