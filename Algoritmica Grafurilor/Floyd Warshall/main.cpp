#include <iostream>
#include <fstream>
#include <climits>
#define inf 9999

using namespace std;

int p[10][10],w[10][10];

ifstream f ("graf.in");

void drum(int s,int d)
{
    if(s!=d)
        drum(s,p[s][d]);
    cout<<d<<" ";
}

int main()
{
    int n,m;
    int nod1,nod2,cost;
    f>>n>>m;
    int d[n][n];

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i!=j)
                w[i][j]=inf;

    for(int i=1; i<=m; i++)
    {
        f>>nod1>>nod2>>cost;
        w[nod1][nod2]=cost;
    }

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            d[i][j]=w[i][j];

            if(w[i][j]==inf)
                p[i][j]=0;
            else if(i!=j)
                p[i][j]=i;
        }

    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(d[i][j]>d[i][k]+d[k][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=p[k][j];
                }

    cout<<"Matricea de predecesori:"<<endl;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            cout<<p[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;
    cout<<"Matricea de distantelor minime:"<<endl;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            cout<<d[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    int sursa,destinatie;
    cout<<"Citire nod sursa: ";
    cin>>sursa;
    cout<<endl;
    cout<<"Citire nod destinatie: ";
    cin>>destinatie;
    cout<<endl;
    cout<<"Drumul minim de la sursa la destinatie este: ";
    drum(sursa,destinatie);

    return 0;
}
