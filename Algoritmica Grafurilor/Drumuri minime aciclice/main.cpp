#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#define infinit 99999
using namespace std;

ifstream fisier("date.in");

vector<int> citire_si_sortare_topologica (vector<pair<int,int> > lista_adiacenta[50],int &n,int &m,int &nod_start)
{
    int nod1,nod2,cost;
    vector<int> grad_intern;
    fisier>>n>>m;

    for(int i=1; i<=n; i++)
        grad_intern.push_back(0);


    for(int i=1; i<=m; i++)
    {
        fisier>>nod1>>nod2>>cost;
        lista_adiacenta[nod1].push_back(make_pair(nod2,cost));
        grad_intern[nod2]++;
    }
    fisier>>nod_start;
    fisier.close();

    vector<int> varfuri_sortate;
    queue<int> coada;
    int x,y;

    //adaugam toate elementele cu grad intern 0 in coada
    for(int i=1; i<=n; i++)
        if(grad_intern[i]==0)
            coada.push(i);

    while(!coada.empty())
    {
        x=coada.front();
        coada.pop();

        varfuri_sortate.push_back(x);
        if(!lista_adiacenta[x].empty())
        {
            for(int i=0; i<=lista_adiacenta[x].size()-1; i++)
            {
                int y=lista_adiacenta[x][i].first;
                grad_intern[y]--;
                if(grad_intern[y]==0)
                    coada.push(y);
            }
        }
    }
    return varfuri_sortate;

}

void lant(int u,int *tata)
{
    if(u!=0)
    {
        lant(tata[u],tata);
        cout<<u<<" ";
    }
}

void aflare_drum_minim(vector<pair<int,int> > lista_adiacenta[50],int n,int nod_start)
{
    int m;
    int *drum=new int[n+1];
    int *tata=new int[n+1];
    int x,y;
    vector<int> varfuri_sortate =citire_si_sortare_topologica(lista_adiacenta,n,m,nod_start);

    for(int i=1; i<=n; i++)
    {
        tata[i]=0;
        drum[i]=infinit;
    }

    drum[nod_start]=0;

    for(int i=0; i<=varfuri_sortate.size()-1; i++)
    {
        x=varfuri_sortate[i];
        if(!lista_adiacenta[x].empty())
        {
            for(int j=0; j<=lista_adiacenta[x].size()-1; j++)
            {
                y=lista_adiacenta[x][j].first;
                if(drum[y]>drum[x]+lista_adiacenta[x][j].second)
                {
                    drum[y]=drum[x]+lista_adiacenta[x][j].second;
                    tata[y]=x;
                }
            }
        }
    }

    cout<<endl;
    cout<<"Vectorul de distante "<<endl;

    for(int i=1; i<=n; i++)
        if(drum[i]==infinit)
            cout<<"infinit ";
        else
            cout<<drum[i]<<" ";
    cout<<endl;

    cout<<"Vectorul de tati (predecesori) "<<endl;

    for(int i=1; i<=n; i++)
        cout<<tata[i]<<" ";
    cout<<endl;

    cout<<"Drumuri de la sursa la fiecare nod:"<<endl;
    for(int i=1; i<=n; i++)
    {
        if(i!=nod_start)
        {
            if(tata[i]!=0)
            {
                lant(i,tata);
                cout<<endl;

            }
            else
                cout<<"Inaccesibil de la nodul de start la nodul "<<i<<endl;
        }
    }

}

int main()
{
    int n,m,nod_start;
    vector<pair<int,int> > lista_adiacenta[50];

    aflare_drum_minim(lista_adiacenta,n,nod_start);
}
