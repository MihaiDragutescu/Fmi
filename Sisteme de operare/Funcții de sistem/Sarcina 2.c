#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv)
{
   int fd1,fd2,count1=1,count2;
   char ch[100];
   
   //deschidem fisierele
   fd1=open(argv[1],O_RDONLY);
   fd2=open(argv[2],O_WRONLY);

   if(fd1==-1 || fd2==-1)//unul din fisiere nu a fost deschis cu succes
   {
      perror("Eroare");
      return errno;
   }
   else//daca ambele fisiere au fost deschise cu succes
   {
      while(count1!=0)//cat timp nu am ajuns la finalul fisierului1
      {
         if((count1=read(fd1,ch,100))<0)//verificam daca avem eroare la citirea din fisier1
         {
            perror("Eroare");
            return errno;
         }
         else if(count1>0)//daca am citit din fisier1
         {
            count2=write(fd2,ch,strlen(ch));//scriem in fisier2

            if(count2<0)//daca avem eroare la scierea in fisier2
            {
               perror("Eroare");
               return errno;
            }
         }
      }
   }
   return 0;
}
