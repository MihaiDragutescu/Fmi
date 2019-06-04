#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char **argv)
{
   int i;
   pid_t pid, wait_pid;

   for(i=1;i<argc;i++)
   {
      pid=fork();
      if(pid<0)
      return errno;
      else if(pid==0)
      {
         int n=atoi(argv[i]);
         printf("%d: ",n);
         while(n!=1)
         {
            if(n%2)
            {
               n=3*n+1;
               printf("%d ",n);
            }
            else
            {
               n=n/2;
               printf("%d ",n);
            }
         }
         printf("\n");
         exit(0);//oprim programul normal
      }
     
   }
   while ((wait_pid=wait(NULL))>0)//cat timp avem procese copil care trebuie terminate
   {
   printf("Done Parent %d Me %d\n",getpid(),wait_pid);//afisam id-ul procesului parinte si al procesului copil
   }

   printf("Done Parent %d Me %d\n",getppid(),getpid());
   return 0;
}
