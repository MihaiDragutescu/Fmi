#include <fstream>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

ifstream f("graf.in");

void citire(int &n,vector<int> *&la)
{
	int i,x,y;
	f>>n;
 	la=new vector<int>[n+1];

	for(i=1;i<=n-1;i++)
    {
		f>>x>>y;
		la[x].push_back(y);
		//neorientat
		la[y].push_back(x);
	}
}


int BF(int s, int n, vector<int> *la, int *tata)
{
	int *viz=new int[n+1];

	int ultim=0;
	queue<int> c;

	int i;
	for(i=1;i<=n;i++)
		viz[i]=0;

	tata[s]=0;


	viz[s]=1;
	c.push(s);
	while(!c.empty())
    {
		int x=c.front();//x- nodul curent
		ultim=x;//va memora ultimul nod din BF = cel mai departat de s

		c.pop();
		for (i=0;i<la[x].size();i++)
        {
			int y=la[x][i];//pentru toti vecinii y ai nodului curent x
			if(viz[y]==0)
				{
					tata[y]=x;
					viz[y]=1;
					c.push(y);
				}
		}
	}
	return ultim;
}

int main()
{
	vector<int> *la;
	int n,m,s;
	int i,j;
	int  *tata;

	citire(n,la);
	f.close();

    tata=new int[n+1];
	int u=BF(1,n,la,tata); //u va fi extremitatea unui lant elementar maxim

	int v=BF(u,n,la,tata); //lantul de la u la v determinat de BF este maxim

	//diametrul = lungimea lantului de la u la v (!numar de muchii)
	int diam=0;
	int x=v;
	while(x!=u)
    {
		diam++;
		x=tata[x];
	}
	int r=(diam+1)/2;
	cout<<"diametrul "<<diam<<endl;
	cout<<"raza "<<r<<endl;
	cout<<"centrul " ;
	/*urcam pana la mijlocul lantului*/
	if(diam%2==0)
	{
		x=v;
		for(i=1;i<=r;i++)
			x=tata[x];
		cout<<x<<" ";

	}
	else
    {
		x=v;
		for(i=1;i<r;i++)
			x=tata[x];
		cout<<x<<" "<<tata[x];

	}


}
