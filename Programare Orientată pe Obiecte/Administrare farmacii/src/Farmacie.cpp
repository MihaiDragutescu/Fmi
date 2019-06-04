#include "Farmacie.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdexcept>
#include <stdio.h>
#include <sstream>



using namespace std;

Farmacie::Farmacie()
{
    denumire=NULL;
    nr_angajati=0;

    for(int i=0;i<=11;i++)
        profit[i]=0;
}

Farmacie::Farmacie(char *denumire1,int nr_angajati1,float profit1[12])
{
    denumire=(char *)malloc(strlen(denumire1)*sizeof(char));
    for(int i=0;i<=11;i++)
        denumire[i]=denumire1[i];

    nr_angajati=nr_angajati1;

    for(int i=0;i<=11;i++)
        profit[i]=profit1[i];
}

Farmacie::Farmacie(Farmacie &f)
{
    denumire=(char *)malloc(256*sizeof(char));
    for(int i=0;i<=strlen(f.denumire)-1;i++)
        denumire[i]=f.denumire[i];

    nr_angajati=f.nr_angajati;

    for(int i=0;i<=11;i++)
        profit[i]=f.profit[i];
}

Farmacie::~Farmacie()
{
    delete denumire;
}

 void Farmacie::afisare(ostream &out)const
{
    out<<"Denumire: "<<denumire<<"; Numar angajati: "<<nr_angajati<<"; Profitul lunar: ";
    for(int i=0;i<=11;i++)
        out<<profit[i]<<" ";
    out<<"; ";
}

char* Farmacie::GetDenumire()
{
    return denumire;
}

int Farmacie::GetAngajati()
{
    return nr_angajati;
}

float Farmacie::GetProfit(int i)
{
    return profit[i];
}

const Farmacie& Farmacie::operator=(const Farmacie& f)
{
  if (this != &f)
  {
      denumire=(char *)malloc(strlen(f.denumire)*sizeof(char));
      for(int i=0;i<=strlen(f.denumire)-1;i++)
        denumire[i]=f.denumire[i];

      nr_angajati=f.nr_angajati;
      for(int i=0;i<=11;i++)
      profit[i]=f.profit[i];
  }

  return *this;
}

istream& operator>>(istream& in, Farmacie& f)
{
    cout << endl << "Dati numele farmaciei: ";
    f.denumire=(char *)malloc(256*sizeof(char));
    in >> f.denumire;


    string s;
    do
    {
        try
        {
            cout << "Numarul de angajati: ";
            cin>>s;

            if (s.find_first_not_of("0123456789") != string::npos)
            {
                throw runtime_error("Formatul nu e valid.\n");
            }

            istringstream buffer(s);
            buffer>>f.nr_angajati;
            break;

        }
        catch (runtime_error error)
        {
            cout << "\nA avut loc o eroare la citire. \n" << error.what();
            continue;
        }
    }
    while(1);

    cout <<"Profitul lunar: \n";
    for(int i=0; i<=11; i++)
    {
        do
        {
            try
            {
                cout << "Profitul pe luna "<<i+1<<" a anului: ";
                cin>>s;

                if (s.find_first_not_of(".0123456789") != string::npos)
                {
                    throw runtime_error("Formatul nu e valid.\n");
                }

                istringstream buffer(s);
                buffer>>f.profit[i];
                break;

            }
            catch (runtime_error error)
            {
                cout << "\nA avut loc o eroare la citire: \n" << error.what();
                continue;
            }
        }
        while(1);

    }

    return in;
}

ostream& operator<<(ostream& out, const Farmacie& f)
{
    f.afisare(out);
    return out;
}

Farmacie_online::Farmacie_online()
{
    adresa_web=NULL;
    vizitatori=0;
    discount=0;
}

Farmacie_online::Farmacie_online(char* _denumire,int _nr_angajati,float _profit[],char* _adresa_web,int _vizitatori,float _discount):Farmacie(_denumire,_nr_angajati,_profit)
{
    adresa_web=(char *)malloc(strlen(_adresa_web)*sizeof(char));
    for(int i=0;i<=strlen(_adresa_web);i++)
        adresa_web[i]=_adresa_web[i];

    vizitatori=_vizitatori;
    discount=_discount;
}

Farmacie_online::Farmacie_online(Farmacie_online &f):Farmacie(f.denumire,f.nr_angajati,f.profit)
{
    adresa_web=(char *)malloc(256*sizeof(char));
    for(int i=0;i<=strlen(f.adresa_web)-1;i++)
        adresa_web[i]=f.adresa_web[i];

    vizitatori=f.vizitatori;
    discount=f.discount;
}

Farmacie_online::~Farmacie_online()
{
    delete adresa_web;
}

 void Farmacie_online::afisare(ostream &out)const
{
    Farmacie::afisare(out);
    out<<"Adresa web: "<<adresa_web<<"; Numar vizitatori: "<<vizitatori<<"; Discountul: "<<discount<<"; ";

}

char *Farmacie_online::GetAdresa()
{
    return adresa_web;
}

int Farmacie_online::GetVizitatori()
{
    return vizitatori;
}

float Farmacie_online::GetDiscount()
{
    return discount;
}

const Farmacie_online & Farmacie_online::operator=(const Farmacie_online& f)
{
    if (this != &f)
    {
        denumire=(char *)malloc(strlen(f.denumire)*sizeof(char));
        for(int i=0; i<=strlen(f.denumire)-1; i++)
            denumire[i]=f.denumire[i];

        nr_angajati=f.nr_angajati;
        for(int i=0; i<=11; i++)
            profit[i]=f.profit[i];
        adresa_web=(char *)malloc(strlen(f.adresa_web)*sizeof(char));
        for(int i=0; i<=strlen(f.adresa_web)-1; i++)
            adresa_web[i]=f.adresa_web[i];

        vizitatori=f.vizitatori;
        discount=f.discount;
    }

    return *this;
}

istream& operator>>(istream& in, Farmacie_online& f)
{
    Farmacie far;
    in >> far;

    f.denumire = (char*) malloc(strlen(far.GetDenumire()) * sizeof(char));
    for(int i=0; i<=strlen(far.GetDenumire()); i++)
        f.denumire[i] = far.GetDenumire()[i];

    f.nr_angajati = far.GetAngajati();

    for(int i=0; i<=11; i++)
        f.profit[i] = far.GetProfit(i);

    cout << endl << "Dati adresa web a farmaciei: ";
    f.adresa_web=(char *)malloc(256*sizeof(char));
    in >> f.adresa_web;

    string s;

    do
    {
        try
        {
            cout << "Numarul de vizitatori: ";
            cin>>s;

            if (s.find_first_not_of("0123456789") != string::npos)
            {
                throw runtime_error("Formatul nu e valid.\n");
            }

            istringstream buffer(s);
            buffer>>f.vizitatori;
            break;

        }
        catch (runtime_error error)
        {
            cout << "\nA avut loc o eroare la citire: \n" << error.what();
            continue;
        }
    }
    while(1);

    do
    {
        try
        {
            cout << "Discount-ul: ";
            cin>>s;

            if (s.find_first_not_of(".0123456789") != string::npos)
            {
                throw runtime_error("Formatul nu e valid\n");
            }

            istringstream buffer(s);
            buffer>>f.discount;

            if (f.discount < 0 || f.discount>100)
            {
                throw std::runtime_error("Numar care nu e cuprins intre 0 si 100.\n");
            }
            break;

        }
        catch (runtime_error error)
        {
            cout << "\nA avut loc o eroare la citire: \n" << error.what();
            continue;
        }
    }
    while(1);

    return in;
}

ostream& operator<<(ostream& out, const Farmacie_online& f)
{
    f.afisare(out);
    return out;
}

template <class T>
const Gestionare_farmacii<T> & Gestionare_farmacii<T>::operator=(const Gestionare_farmacii<T>& f)
{
  if (this != &f)
  {
      v = f.v;
  }

  return *this;
}


template <class T>
ostream& operator<<(ostream& out, const Gestionare_farmacii<T>& f)
{
    out<<" Id-ul: " <<f.id<<endl;
    cout<<"Informatii farmacii:";

    for(int i=0;i<=f.v.size()-1;i++)
        out<<*(f.v[i]);

    return out;
}

const Gestionare_farmacii<unsigned> & Gestionare_farmacii<unsigned>::operator=(const Gestionare_farmacii<unsigned>& f)
{
  if (this != &f)
  {
      numar_vizitatori = f.numar_vizitatori;
  }

  return *this;
}


ostream& operator<<(ostream& out, const Gestionare_farmacii<unsigned>& f)
{
   out<<"Numarul de vizitatori:"<<f.numar_vizitatori;
   return out;
}

