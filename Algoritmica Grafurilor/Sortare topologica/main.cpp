#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fisier("graf.in");

void citire(int &n,int &m,vector<int> *&lista_adiacenta,int *&grad_intern)
{
    int x,y;
    fisier>>n>>m;
    lista_adiacenta=new vector<int>[n+1];
    grad_intern=new int[n+1];

    for(int i=1;i<=n;i++)
        grad_intern[i]=0;

    for(int i=1;i<=m;i++)
    {
        fisier>>x>>y;
        lista_adiacenta[x].push_back(y);
        grad_intern[y]++;
    }

}

vector<int> sortare_topologica(int n,int m,vector<int> *lista_adiacenta,int *grad_intern)
{
    vector <int> varfuri_sortate;
    queue <int> coada;

    int x,y;

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
                y=lista_adiacenta[x][i];
                grad_intern[y]--;
                if(grad_intern[y]==0)
                    coada.push(y);
            }
        }
    }

    return varfuri_sortate;
}

int main()
{
    int n,m,*grad_intern;
    vector<int> *lista_adiacenta;
    vector<int> varfuri_sortate;

    citire(n,m,lista_adiacenta,grad_intern);

    varfuri_sortate=sortare_topologica(n,m,lista_adiacenta,grad_intern);

    for(int i=0;i<=varfuri_sortate.size()-1;i++)
        cout<<varfuri_sortate[i]<<" ";

    return 0;
}
