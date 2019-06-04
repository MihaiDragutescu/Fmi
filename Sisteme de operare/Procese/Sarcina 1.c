#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char **argv)
{
   pid_t pid=fork();//cream un proces nou(proces copil,copie a procesului apelant)
   
   if(pid<0)//verificam daca avem eroare la crearea procesului copil
      return errno;
   else if(pid==0)//instructiuni pentru copil
   {
      char *arggv[]={"ls",NULL};
      execve("/bin/ls",arggv,NULL);//se executa programul suprascriind complet procesul apelant cu un nou proces conform programului gasit la calea indicata
      perror(NULL);
   }
   else//instructiuni pentru parinte
   {
      wait(NULL);//asteapta terminarea procesului copil
      printf("My PID=%d Child=%d\n",getpid(),pid);//afisam id-ul procesului curent si al procesului copil
   }
   return 0;
}
