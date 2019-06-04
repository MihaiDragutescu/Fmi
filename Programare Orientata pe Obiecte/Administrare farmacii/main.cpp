#include <iostream>
#include "Farmacie.h"
#include <cstring>
#include <sstream>
#include <stdexcept>

using namespace std;

void print_menu()
{
    cout<<"F: Citire date farmacie simpla."<<endl;
    cout<<"O: Citire date farmacie online."<<endl<<endl;
}
template <class T>
int Gestionare_farmacii<T>::index;

int main()
{
    char aux;
    int n;
    string s;

    do
    {
        try
        {
            cout << "\nCate farmacii urmeaza sa fie citite? ";
            cin >> s;

            if (s.find_first_not_of("0123456789") != string::npos)
            {
                throw "Formatul nu e valid";
            }

            istringstream buffer(s);
            buffer>>n;
            break;

        }
        catch (const char * error)
        {
            cout << "\nA avut loc o eroare la citire: \n" <<error;
            continue;
        }
    }
    while(1);

    Gestionare_farmacii <Farmacie> _gestionare_farmacii(1);
    Gestionare_farmacii <unsigned> gestiune_vizitatori;

    for(int i=0; i<n; i++)
    {
        cout<<endl;
        cout<<"Alegeti o varianta: "<<endl;
        print_menu();
        cin>>aux;
        aux = toupper(aux);
        switch (aux)
        {
        case 'F':
        {
            Farmacie *farmacie_simpla=new Farmacie;
            cin>>*farmacie_simpla;
            _gestionare_farmacii+=*(farmacie_simpla);
        }
        break;
        case 'O':
        {
            Farmacie_online *farmacie_online=new Farmacie_online;
            cin>>*farmacie_online;
            _gestionare_farmacii+=*farmacie_online;
            gestiune_vizitatori.setNumarVizitatori(gestiune_vizitatori.getNumarVizitatori()+farmacie_online->GetVizitatori());
        }
        break;


        default:
            cout << aux << "Eroare." << endl;
            i--;
        }
    }

    vector <Farmacie *>v=_gestionare_farmacii.GetFarmacie();
    cout<<endl;
    for(int i=0; i<=v.size()-1; i++)
    {
        if (Farmacie_online* farm_on = dynamic_cast<Farmacie_online*>(v[i]))
        {
            cout << endl << "Farmacie online: " << *farm_on;
        }

        else if (Farmacie* farm_s = dynamic_cast<Farmacie*>(v[i]))
        {
            cout << endl << "Farmacie simpla: " << *farm_s;
        }
    }
    cout<<endl;
    cout <<"Indexul farmaciei:"<<Gestionare_farmacii<Farmacie>::GetIndex()<<endl;
    cout <<gestiune_vizitatori;
    cout<<endl;
}
