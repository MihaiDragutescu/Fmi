#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream f("date.in");

int stari_finale[10];
string a[10][10];
int numar_stari,numar_stari_finale,stare1,stare2,lungime_cuvant,numar_simboluri;
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
        int i=0;
        while(i<=numar_simboluri-1 && ok==0)
        {
            if(aux==alfabet[i])
            {
                ok=1;
                a[stare1][stare2]+=aux;
            }
            i++;
        }
        if(!ok)
            break;
    }
}
string c;
int lungime;

     for(int i=0;i<=numar_stari-1;i++)
         for(int j=0;j<=numar_stari-1;j++)
         {
            if(a[i][j].length()>1)
                {
                    c=a[i][j];
                    lungime=c.length();
                    c[lungime-1]=0;
                    a[i][j]=c;
                }
            if(a[i][j].empty())
                a[i][j]='0';
         }
    return ok;
}
void verificare(int numar_stari,int lungime_cuvant)
{
    int temp,ok,noua_stare1=0;
    char x;
    string c;
    int i=0,j;

    if(cuvant[0]=='&')
     if(stari_finale[0]==0)
        ok=1;
    else
        ok=0;

    else{
    while(i<=lungime_cuvant-1)
    {
        stare1=noua_stare1;
        ok=0;
        x=cuvant[i];

        for(j=0;j<=numar_stari-1;j++)
        {
            c=a[stare1][j];

                for(int k=0;k<=c.length()-1;k++)
                {
                    if(x==c[k])
                    {
                        noua_stare1=j;
                        ok=1;
                        break;
                        cout<<a[stare1][j]<<" ";
                    }
                }
        }
        i++;
        if(!ok)
            break;
    }
    }

    int ok2=0;

    if(!ok)
        cout<<"Cuvantul nu apartine limbajului recunoscut de automat.";
    else
    {
        cout<<"Starea finala este: "<<noua_stare1;
        cout<<endl;
        for(int i=0;i<=numar_stari_finale-1;i++)
        {
            if(stari_finale[i]==noua_stare1)
                ok2=1;
        }

        if(ok2==1)
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
        cout<<endl;
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
