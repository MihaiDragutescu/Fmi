#include <iostream>
#include <fstream>

using namespace std;

ifstream f("date.in");

int a[10][10],stari_finale[10];
int numar_stari,numar_stari_finale,lungime_cuvant,stare1,stare2,numar_simboluri;
char alfabet[10],cuvant[10];

int citire_date(int &numar_stari,int &lungime_cuvant)
{
    int ok=0;
    char aux,x;
    f>>numar_stari;
    f>>numar_stari_finale;

    for(int i=0;i<=numar_stari_finale-1;i++)
        f>>stari_finale[i];

    f>>numar_simboluri;
    for(int i=0;i<=numar_simboluri-1;i++)
        f>>alfabet[i];

    f>>lungime_cuvant;
    int nr=0;

    for(int i=0;i<=lungime_cuvant-1;i++)
    {
        f>>cuvant[i];
        x=cuvant[i];
        for(int j=0;j<=numar_simboluri-1;j++)
            if(x==alfabet[j])
            nr++;
    }
    if(nr==lungime_cuvant)
        ok=1;
    if(ok){
    while(!f.eof())
    {
        ok=0;
        f>>stare1;
        f>>aux;
        f>>stare2;
        for(int i=0;i<=numar_simboluri-1;i++)
        {
            if(aux==alfabet[i])
            {
                a[stare1][stare2]=int(aux);
                ok=1;
            }

        }
        if(!ok)
            break;
    }
    }
    return ok;
}
void verificare(int numar_stari,int lungime_cuvant)
{

    int aux,ok,noua_stare1=0;
    char x;
    int i=0,j;
    while(i<=lungime_cuvant-1)
    {
        stare1=noua_stare1;
        ok=0;

        x=cuvant[i];
        aux=int(x);

        for(j=0;j<=numar_stari-1;j++)
        {
            if(a[stare1][j]==aux)
            {
                noua_stare1=j;
                ok=1;
                break;
            }

        }
        i++;
        if(!ok)
            break;

    }
    int ok2=0;
    if(!ok)
        cout<<"Cuvantul nu apartine limbajului recunoscut de automat.";
    else
    {
        for(int i=0;i<=numar_stari_finale-1;i++)
            if(stari_finale[i]==noua_stare1)
                ok2=1;

        if(ok2)
            cout<<"Cuvantul apartine limbajului recunoscut de automat.";
        else
            cout<<"Cuvantul nu apartine limbajului recunoscut de automat.";
    }


}
void afisare(int numar_stari,int lungime_cuvant)
{
    for(int i=0;i<=numar_stari-1;i++)
    {
        for(int j=0;j<=numar_stari-1;j++)
        cout<<a[i][j]<<" ";
        cout<<"\n";
    }
    cout<<endl;
    for(int i=0;i<=lungime_cuvant-1;i++)
        cout<<cuvant[i];
        cout<<" ";
}
int main()
{
   if(citire_date(numar_stari,lungime_cuvant)==0)
    cout<<"S-a identificat un caracter ce nu apartine alfabetului.";
   else
   {
       citire_date(numar_stari,lungime_cuvant);
       afisare(numar_stari,lungime_cuvant);
       verificare(numar_stari,lungime_cuvant);
   }

    return 0;
}
