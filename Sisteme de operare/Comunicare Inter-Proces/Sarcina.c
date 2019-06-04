#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
   printf("Starting parent %d\n",getpid());

   pid_t pid,wait_pid;
   int size=4096;
   char shm_collatz[]="collatz";
   int shm_fd=shm_open(shm_collatz,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);//cream obiect de memorie partajata
   
   if(shm_fd<0)
   {
      perror(NULL);
      return errno;
   }

   size_t shm_size=size*argc;

   if(ftruncate(shm_fd,shm_size)==-1)//definim dimensiunea(marim obiectul shm_fd de la 0 la size*argc bytes
   {
      perror(NULL);
      shm_unlink(shm_collatz);//stergem obiectele create
      return errno;
   }

   int i;
   for(i=1;i<argc;i++)
   {
      pid=fork();
      if(pid<0)
         return errno;
      else if(pid==0)
      {
         char *shm_ptr=mmap(0,size,PROT_WRITE,MAP_SHARED,shm_fd,(i-1)*size);//incarcam in spatiul procesului memoria partajata. shm_ptr- pointer catre adresa din spatiul procesului la care a fost incarcat obiectul
         if(shm_ptr==MAP_FAILED)//daca avem eroare la incarcarea memoriei
         {
            perror(NULL);
            shm_unlink(shm_collatz);
            return errno;
         }
         int n=atoi(argv[i]);
         sprintf(shm_ptr,"%d: %d ",n,n);

         while(n!=1)
         {
            if(n%2)
               n=3*n+1;      
            else
               n=n/2;
            char buffer[20];
            sprintf(buffer,"%d ",n);//retinem n la fiecare pas intr-un buffer
            strcat(shm_ptr,buffer);
         }
         strcat(shm_ptr,"\n");
         munmap(shm_ptr,size);//nu mai avem nevoie de memorie
         exit(0);
      }
   }   
   
   while ((wait_pid=wait(NULL))>0)
   {
      printf("Done Parent %d Me %d\n",getpid(),wait_pid);
   }

   char *shm_ptr=mmap(0,shm_size,PROT_READ,MAP_SHARED,shm_fd,0);
   if(shm_ptr==MAP_FAILED)
   {
      perror(NULL);
      shm_unlink(shm_collatz);
      return errno;
   }   
   
   for(i=1;i<=argc;i++)
   {
      printf("%s",shm_ptr+size*(i-1));//afisam sirul obtinut pentru fiecare numar accesand zona de memorie la care a fost salvat
   }
   munmap(shm_ptr,shm_size);
   shm_unlink(shm_collatz);
   printf("Done Parent %d Me %d\n",getppid(),getpid());  
 
   return 0;
}
