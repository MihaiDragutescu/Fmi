#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#define infinit 999999

using namespace std;

fstream f("graf.in");

struct muchie
{
    int varf_initial,varf_final;
    int cost;
};

void afiseaza(int n, int *r)
{
	int k;
    for(k=1;k<=n;k++)
     	cout<<r[k]<<"  ";
    cout<<endl;
}

void afiseaza_distante(int n, int *r)
{
    int k;
    for(k=1; k<=n; k++)
        if(r[k]<infinit)
            cout<<r[k]<<"  ";
        else
            cout<<"infinit ";
    cout<<endl;
}
void afisare_muchii(muchie m)
{
    cout<<"("<<m.varf_initial<<", "<<m.varf_final<<") cost "<<m.cost<<endl;
}

void citire(vector<pair<int,int> > *&lista_adiacenta,int &n,int &m)
{
    int nod1,nod2,cost,i;
    f>>n;
	f>>m;
	lista_adiacenta=new vector<pair<int,int> >[n+1];//graf- memorat cu liste de adiacenta

    //citim muchiile
	for(i=1;i<=m;i++)
    {
		f>>nod1>>nod2>>cost;
		lista_adiacenta[nod1].push_back(make_pair(nod2,cost));
		lista_adiacenta[nod2].push_back(make_pair(nod1,cost));
	}
	f.close();
}

void Prim(int nod_start, int n, vector<pair<int,int> > *lista_adiacenta,  vector<muchie> &muchii_apcm)
{
	int u,*tata,*viz,i,v,j;
	int *distanta,w_uv;


	//*initializare d,tata,viz
	distanta=new int[n+1];
	tata=new int[n+1];
	viz=new int[n+1];

	for(u=1;u<=n;u++)
    {
		viz[u]=tata[u]=0;
		distanta[u]=infinit;
	}
	distanta[nod_start]=0;

	/*Q - set (arbore binar de cautare - inserare, cautare, stergere - complexitate logaritmica)
	spre deosebire de priority_queue, are metoda de cautare => nu inserez de mai multe ori in Q un varf */

//	set <muchie_min_varf, comparator_muchie_min_varf> Q;
	set <pair<int,int> > Q;
	Q.insert({distanta[nod_start],nod_start}); //suficient sa inseram in Q doar varful de start, nu toate varfurile, pentru ca nu facem actualizarea etichetei, ci stergere+reinserare
	for(i=1;i<=n-1;i++)
    {
		//u=(*Q.begin()).second;//varful nevizitat cu d minim
		u=Q.begin()->second;
		Q.erase(Q.begin());
		viz[u]=1;
		cout<<"Extras "<<u<<endl;

		//actualizam etichetele vecinilor nevizitati
		for(j=0;j<lista_adiacenta[u].size();j++)
        {
			v=lista_adiacenta[u][j].first;
			w_uv=lista_adiacenta[u][j].second;
			if(viz[v]==0)
            {
                if(distanta[v]>w_uv)
                {
					tata[v]=u;
			        Q.erase(make_pair(distanta[v],v)); //sterg perechea daca exista
					distanta[v]=w_uv;
  				    Q.insert(make_pair(distanta[v],v)); //adaug noua pereche v,d[v]
  				}
			}
		}
		cout<<"d:   ";
		afiseaza_distante(n,distanta);
		cout<<"tata:";
		afiseaza(n,tata);
	}

	for(u=1;u<=n;u++)
		if(tata[u]!=0) //u!=s
			muchii_apcm.push_back({u,tata[u],distanta[u]});
}
int main()
{

	int m,n,x,y,c,i,j,nod_start,mc;
    vector<pair<int,int> > *lista_adiacenta;
    citire(lista_adiacenta,n,m);

    vector<muchie> muchii_apcm;
    cout<<"Introduceti varful de start ";
    cin>>nod_start;
    Prim(nod_start,n,lista_adiacenta,muchii_apcm);


    if (muchii_apcm.size()<n-1) cout<<"graful nu este conex";
    else
    {
    	double cost=0;
    	cout<<endl<<"Muchiile arborelui de cost minim:"<<endl;
    	for(mc=0;mc<muchii_apcm.size();mc++)
    	{
			afisare_muchii(muchii_apcm[mc]);
    		cost+=muchii_apcm[mc].cost;
    	}
    	cout<<"Cost total "<<cost;
	}
	return 0;
}
