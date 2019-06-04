#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include<algorithm>
using namespace std;

/*
Idee - la un pas unim varful de grad maxim cu urmatoarele in ordine descrescatoare a gradelor

Pentru a reordona secventa la fiecare pas -este suficient sa inversam vectsorul de grade intre pozitiile intre care s-a stricat ordinea
Spre exemplu, pentru secventa
5 4 4 3 3 3 3 3 2 1 1, dupa un pas, obtinem secventa
0 3 3 2 2 2 3 3 2 1 1- reordonam intre pozitiile 4 si 8 <=> inversam/oglindim aceasta parte din vector

*/
ifstream fisier ("date.in");

int citire(vector<pair<int,int> > &varfuri,int &n)
{
    int gr,et,suma_grade=0,valid=1;
    fisier>>n;

    for(int i=1;i<=n;i++)
    {
        fisier>>gr;
        if(gr>=n)
        {
            valid=0;
            break;
        }
        varfuri.push_back(make_pair(i,gr));
        suma_grade+=gr;
    }

    fisier.close();

    if(suma_grade%2==1)
        valid=0;

    return valid;
}

int comparare(const pair<int,int> &a,const pair<int,int> &b)
{
    return a.second>b.second;
}

void creare_graf(vector<pair<int,int> > varfuri,int n)
{
    vector<pair<int,int> > muchii;
    int i,j,valid=1;

    if(citire(varfuri,n)==0)
        cout<<"Varfurile date nu pot forma un graf.";
    else
    {
        sort(varfuri.begin(),varfuri.end(),comparare);

        i=0;
        while(varfuri[i].second>0 && valid==1)
        {
            valid=1;
            for(j=1; j<=varfuri[i].second; j++)
            {
                varfuri[i+j].second--;
                if(varfuri[i+j].second<0)
                {
                    valid=0;
                    cout<<"Varfurile date nu pot forma un graf.";
                    break;
                }
                else
                    muchii.push_back(make_pair(varfuri[i].first,varfuri[i+j].first));
            }

            varfuri[i].second=0;
            sort(varfuri.begin(),varfuri.end(),comparare);

        }

        if(valid)
        {
            cout<<"Muchiile grafului format sunt:"<<endl;
             for(i=0; i<=muchii.size()-1; i++)
            cout<<muchii[i].first<<"-"<<muchii[i].second<<endl;
        }
        else
            cout<<"Varfurile date nu pot forma un graf.";
    }
}

int main()
{
    vector<pair<int,int> > varfuri;
    int n;
    creare_graf(varfuri,n);
    return 0;
}
