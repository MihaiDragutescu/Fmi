#include <iostream>
#include<fstream>
#include <queue>
#include <cstring>
#define NMX 9999

using namespace std;

ifstream fin("graf.in");

int tata[NMX],viz[NMX];
int n,m;

vector<int> lista_adiacenta[NMX];
vector<int> lista_adiacenta_intrare[NMX];
int flux[NMX][NMX],cost[NMX][NMX];

int BF(int sursa)
{
    int x;

    memset(tata,0,sizeof(tata));
    memset(viz,0,sizeof(viz));

    queue<int> coada;
    coada.push(sursa);
    viz[sursa]=1;

    while(coada.size()>0)
    {
        x=coada.front();
        coada.pop();

        for(int i=0;i<lista_adiacenta[x].size();i++)
        {
            int y=lista_adiacenta[x][i];
            if(viz[y]==0 && flux[x][y]<cost[x][y])
            {
                tata[y]=x;
                if(y==n)
                    return 1;

                coada.push(y);
                viz[y]=1;
            }
        }

        for(int i=0;i<lista_adiacenta_intrare[x].size();i++)
        {
            int y=lista_adiacenta_intrare[x][i];
            if(viz[y]==0 && flux[y][x]>0)
            {
                tata[y]=-x;
                if(y==n)
                    return 1;

                coada.push(y);
                viz[y]=1;
            }
        }
    }
    return 0;
}

void lant(int u,int *tata)
{
    if(u!=0)
    {
        lant(tata[u],tata);
        cout<<u<<" ";
    }
}

int main()
{
    int nod1,nod2;
    int c;

    fin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        fin>>nod1>>nod2>>c;
        lista_adiacenta[nod1].push_back(nod2);
        lista_adiacenta_intrare[nod2].push_back(nod1);//liste adiacenta intrare
        cost[nod1][nod2]=c;
        flux[nod1][nod2]=0;
    }

    fin.close();

    int flux_maxim=0;
    int sursa=1;//sursa
    int destinatie=n;//destinatia

    while(BF(sursa))
    {

		//calculam i(P) = capacitatea reziduala minima pe un arc de pe drumul de la s la t determinat cu bf
        int iP=9999; //i(P)
        destinatie=n;
        cout<<"lantul: ";
        while(destinatie!=sursa)
        {
            if(tata[destinatie]>=0)
            {
                //arc direct - capacitate c(e)-f(e)
                if(cost[tata[destinatie]][destinatie]-flux[tata[destinatie]][destinatie]<iP)
                    iP= cost[tata[destinatie]][destinatie]-flux[tata[destinatie]][destinatie];
                destinatie=tata[destinatie];
            }
            else
            {
                //arc invers - capacitate f(e)
                if( flux[destinatie][-tata[destinatie]]<iP)
                    iP= flux[destinatie][-tata[destinatie]];
                destinatie=-tata[destinatie];
            }

        }

        lant(n,tata);

        cout<<" capacitate "<<iP<<endl;
          //revizuim fluxul de-a lungul lantului determinat
        destinatie=n;
        while(destinatie!=sursa)
        {
            if(tata[destinatie]>=0 )
            {
                //arc direct - creste fluxul cu iP
                flux[tata[destinatie]][destinatie]+=iP;
                destinatie=tata[destinatie];
            }
            else
            {
                //arc invers - scade fluxul cu iP
                flux[destinatie][-tata[destinatie]]-=iP;
                destinatie=-tata[destinatie];
            }
        }
        flux_maxim+=iP; //creste valoarea fluxului cu iP

    }
    cout<<"-----------------------------------------"<<endl;
    cout<<"valoarea fluxului maxim = "<<flux_maxim<<endl;
    cout<<"un flux maxim: "<<endl;

    for(int u=1;u<=n;u++)
    	for(int j=0;j<lista_adiacenta[u].size();j++)
        {
    		int v=lista_adiacenta[u][j];
    		cout<<"arcul "<<u<<" "<<v<<" flux "<<flux[u][v]<<endl;
		}

    return 0;
}
