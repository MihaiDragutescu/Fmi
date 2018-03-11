#include <iostream>
#include <cstring>
#include"Polinom.h"

using namespace std;

Polinom readPolynomial()
{
    int max_degree;
    double value;
    Polinom poly;

    std::cout<<"Introduceti gradul polinomului: ";
    std::cin>>max_degree;
    poly.setDegree(max_degree);

    for (int i=max_degree;i>=0;i--)
    {
        std::cout<<"Introduceti coeficientul pentru x^" << i << ": ";
        std::cin>>value;
        poly.setCoef(i,value);
    }
    return poly;
}

void print_menu()
{
    cout<<endl;
    cout<<" E   Evaluare polinom intr-un punct" << endl;
    cout<<" P   Afisati un polinom" << endl;
    cout<<" +   Suma a doua polinoame" << endl;
    cout<<" -   Diferenta a doua polinoame" << endl;
    cout<<" *   Produsul a doua polinoame" << endl;
    cout<<" Q   Quit this test program" << endl;
}

int main()
{
    char aux;
    int num,x;
    double value;
    Polinom poly1, poly2, result;

    cout<<"Dati primul polinom: "<<endl;
    poly1 = readPolynomial();

    cout<<"Dati al doilea polinom: "<<endl;
    poly2 = readPolynomial();

    do
    {
        cout<<endl;
        cout<<"Alegeti o varianta: ";
        print_menu();
        cin>>aux;
        aux = toupper(aux);

        switch (aux)
        {
            case 'E':
                cout<<"Introduceti o valoare: ";
                cin>>x;
                cout<<"Evaluati polinomul 1 sau 2: ";
                cin>>num;
                if(num>2)
                {
                    cout<<"Eroare.";
                    cout<<endl;
                }
                else
                {
                    cout<<"Valoarea polinomului este ";
                    if(num==1)
                        cout<<poly1.evaluate(x);
                    else
                        cout<<poly2.evaluate(x);
                    cout<<endl;
                }
                break;
            case 'P':
                cout << "Afisati polinomul 1 sau polinomul 2? ";
                cin >> num;
                if ( num == 1 )
                    poly1.printPolynomial();
                else if ( num == 2 )
                    poly2.printPolynomial();
                else
                    cout << "Introduceti alta valoare" << endl;
                break;
            case '+':
                      cout<<"Suma polinoamelor este:" << endl;
                      result=poly1+poly2;
                      result.printPolynomial();
                      break;
             case '-':
                      cout<<"Diferenta polinoamelor este:" << endl;
                      result=poly1-poly2;
                      result.printPolynomial();
                      break;
            case '*':
                      cout<<"Produsul polinoamelor este:" << endl;
                      result=poly1*poly2;
                      result.printPolynomial();
                      break;
            case 'Q': cout << "Program terminat." << endl;
                      break;
            default:  cout << aux << "Eroare." << endl;
        }
    }while ((aux != 'Q'));

}

