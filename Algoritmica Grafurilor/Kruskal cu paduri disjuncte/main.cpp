#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fisier ("kruskal.in");

struct muchie
{
    int varf_initial,varf_final;
    int cost;
};

void citire(muchie *&muchii,int &n,int &m)
{
    fisier>>n>>m;

    muchii=new muchie[m];
    for(int i=0;i<=m-1;i++)
    {
        fisier>>muchii[i].varf_initial>>muchii[i].varf_final>>muchii[i].cost;
    }
}

void initializare(int u,int *tata,int *h)
{
    tata[u]=h[u]=0;
}

int comparare(muchie x,muchie y)
{
    if(x.cost<y.cost)
        return 1;
    return 0;
}

int reprez(int u,int *tata)
{
    if(tata[u]==0)
        return u;
    tata[u]=reprez(tata[u],tata);
    return tata[u];
}

void reuneste(int u,int v,int *tata,int *h)
{
    int ru,rv;
    ru=reprez(u,tata);
    rv=reprez(v,tata);
    if(h[ru]>h[rv])
        tata[rv]=ru;
    else
    {
        tata[ru]=rv;
        if(h[ru]==h[rv])
            h[rv]++;
    }

}

void kruskal(int n,int m,muchie *muchii,vector<muchie> &arbore_partial_cost_minim)
{
    int *tata,*h,u,v,numar_muchii_selectate=0;

    tata=new int[n+1];
    h=new int[n+1];

    for(int i=1;i<=n;i++)
        initializare(i,tata,h);

    citire(muchii,n,m);
    sort(muchii,muchii+m,comparare);

    cout<<"Muchiile sortate dupa cost:"<<endl;
    for(int i=0;i<=m-1;i++)
        cout<<muchii[i].varf_initial<<" "<<muchii[i].varf_final<<" "<<muchii[i].cost<<endl;
    cout<<endl;

    for(int i=0;i<=m-1;i++)
    {
        cout<<"Muchia curenta: "<<muchii[i].varf_initial<<" "<<muchii[i].varf_final<<" "<<muchii[i].cost<<endl;

        u=muchii[i].varf_initial;
        v=muchii[i].varf_final;

        if(reprez(u,tata)!=reprez(v,tata))
        {
            numar_muchii_selectate++;
            arbore_partial_cost_minim.push_back(muchii[i]);

            reuneste(u,v,tata,h);

            if(numar_muchii_selectate==n-1)
                break;

        }
        cout<<"Vectorul tata: ";
        for(int i=1; i<=n; i++)
            cout<<tata[i]<<" ";

        cout<<"Vectorul h: ";
        for(int i=1; i<=n; i++)
            cout<<h[i]<<" ";
        cout<<endl;

    }

    cout<<"Vectorul tata: ";
    for(int i=1; i<=n; i++)
        cout<<tata[i]<<" ";

    cout<<"Vectorul h: ";
    for(int i=1; i<=n; i++)
        cout<<h[i]<<" ";
    cout<<endl;

    if (arbore_partial_cost_minim.size()<n-1)
        cout<<"Graful nu este conex";
    else
    {
        int cost=0;
        cout<<endl<<"Muchiile arborelui partial optim:"<<endl;
        for(int i=0; i<=arbore_partial_cost_minim.size()-1; i++)
        {
            cout<<arbore_partial_cost_minim[i].varf_initial<<" "<<arbore_partial_cost_minim[i].varf_final<<" "<<arbore_partial_cost_minim[i].cost<<endl;
            cost+=arbore_partial_cost_minim[i].cost;
        }
        cout<<"Cost total: "<<cost;
    }

}

int main()
{
    muchie *muchii;
    vector<muchie> arbore_partial_cost_minim;
    int n,m;
    kruskal(n,m,muchii,arbore_partial_cost_minim);

    return 0;
}
