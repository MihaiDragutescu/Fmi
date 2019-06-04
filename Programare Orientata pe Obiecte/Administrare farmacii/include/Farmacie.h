#include <iostream>
#ifndef FARMACIE_H
#define FARMACIE_H
#include <vector>

using namespace std;

class Farmacie
{
    protected:
        char *denumire;
        int nr_angajati;
        float profit[12];

    public:
        Farmacie();
        Farmacie(char*,int,float[]);
        Farmacie(Farmacie&);
        virtual ~Farmacie();

        virtual void afisare(ostream&) const;
        char* GetDenumire();
        int GetAngajati();
        float GetProfit(int);

       const Farmacie& operator = (const Farmacie&);
       friend istream& operator >> (istream&, Farmacie&);
       friend ostream& operator << (ostream&, const Farmacie&);

};

class Farmacie_online : public Farmacie
{

    protected:
        char *adresa_web;
        int vizitatori;
        float discount;

    public:
        Farmacie_online();
        Farmacie_online(char* _denumire,int _nr_angajati,float _profit[],char* _adresa_web,int _vizitatori,float _discount);
        Farmacie_online(Farmacie_online& );
        virtual ~Farmacie_online();

        void afisare(ostream&) const;
        char *GetAdresa();
        int GetVizitatori();
        float GetDiscount();

       const Farmacie_online& operator = (const Farmacie_online&);
       friend istream& operator >> (istream&, Farmacie_online&);
       friend ostream& operator << (ostream&, const Farmacie_online&);


};

template <class T>
class Gestionare_farmacii
{
    protected:
        static int index;
        const int id;
        vector <T*> v;

    public:
        Gestionare_farmacii();
        Gestionare_farmacii(int _id): id (_id){}
        Gestionare_farmacii(Gestionare_farmacii& f): id (f.id), v(f.v){}
        virtual ~Gestionare_farmacii(){for(int i=0;i<=v.size()-1;i++)delete v[i];}

        static int GetIndex(){return index;}
        int GetId(){return id;}
        vector <T*> GetFarmacie(){return v;}

       const Gestionare_farmacii& operator = (const Gestionare_farmacii&);
       friend istream& operator >> (istream&, Gestionare_farmacii&);
       friend ostream& operator << (ostream&, const Gestionare_farmacii&);
       Gestionare_farmacii& operator += (T& f)
       {
            v.push_back(&f);
            index++;
            return *this;
       }

};

template <>
class Gestionare_farmacii<unsigned>
{
    protected:
        int numar_vizitatori;

    public:
        Gestionare_farmacii(){numar_vizitatori=0;}
        Gestionare_farmacii(int _numar_vizitatori){numar_vizitatori=_numar_vizitatori;}
        Gestionare_farmacii(Gestionare_farmacii& f){numar_vizitatori=f.numar_vizitatori;}
        virtual ~Gestionare_farmacii(){}

        int getNumarVizitatori(){return numar_vizitatori;}
        int setNumarVizitatori(int _numar_vizitatori){numar_vizitatori=_numar_vizitatori;}

       const Gestionare_farmacii& operator = (const Gestionare_farmacii&);
       friend istream& operator >> (istream&, Gestionare_farmacii&);
       friend ostream& operator << (ostream&, const Gestionare_farmacii&);

};

#endif // FARMACIE_H
