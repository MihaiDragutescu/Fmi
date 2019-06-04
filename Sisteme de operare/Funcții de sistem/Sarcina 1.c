#include <errno.h>
#include <unistd.h>

int main()
{
   char mesaj[10]="Un mesaj\n";
   int var;
   var=write(1,mesaj,10);

   if(var<0)//verificam daca avem eroare la scrierea in fisier
   {
      perror("Eroare");
      return errno;
   }
   return 0;
}
