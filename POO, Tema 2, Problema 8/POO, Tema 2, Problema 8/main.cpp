#include <iostream>
#include "Polinom.h"

using namespace std;

void print_menu()
{
    cout<<"A: Afisare polinom."<<endl;
    cout<<"I: Verificare polinom ireductibil."<<endl;
    cout<<"R: Verificare polinom reductibil."<<endl;
    cout<<"U: Cititi urmatorul polinom."<<endl;
}

int Polinom::nr_obiecte;

int main()
{
    int n;
    char aux;

    cout<<"Cate polinoame urmeaza sa fie citite?"<<endl;
    cin>>n;

    Polinom *p[n],poly;

    for(int i=0;i<n;i++)
    {

        cin>>poly;
        do
        {
            cout<<"Alegeti o varianta: ";
            print_menu();
            cin>>aux;
            aux = toupper(aux);
            switch (aux)
            {
            case 'A':
                cout<<poly;
                cout<<endl;
                break;
            case 'I':
                if(poly.verifica()==1){
                    Polinom_ireductibil* polyI = new Polinom_ireductibil(poly);
                    cout<<"Polinomul verifica criteriul lui Eisenstein, deci e ireductibil."<<endl;
                    p[i]=polyI;
                    break;
                }
                else
                    cout<<"Polinomul nu verifica criteriul lui Eisenstein."<<endl;
            case 'R': {
                Polinom_reductibil* polyR = new Polinom_reductibil(poly);
                if(polyR->verifica()){
                    cout<<"Polinomul e reductibil."<<endl;
                    p[i]=polyR;
                }
                else{
                    Polinom_ireductibil* polyI = new Polinom_ireductibil(poly);
                    cout<<"Polinouml e ireductibil."<<endl;
                    p[i] = polyI;
                }
                break;
            }
            case 'U':
                cout<<"Cititi urmatorul polinom." << endl;
                break;
            default:
                cout << aux << "Eroare." << endl;
            }
        }
        while(aux!='U');
    }

    for(int i=0;i<n;i++)
    {
        if (Polinom_ireductibil* polyR = dynamic_cast<Polinom_ireductibil*>(p[i]))
        {
          cout << endl << "Polinom ireductibil: " << *polyR;
        }

        else if (Polinom_reductibil* polyI = dynamic_cast<Polinom_reductibil*>(p[i]))
        {
            cout << endl << "Polinom reductibil: " << *polyI;
        }
    }

    for(int i=0;i<n;i++)
        delete p[i];

     cout<<"Numar obiecte:"<<Polinom::getObiect();
}
