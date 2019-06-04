#include "Polinom.h"
#include<cmath>

int prim(int n)
{
    if(n==0 || n==1)
        return 0;
    else
    {
        for(int i=2;i<=n/2;i++)
        if(n%i==0)
            return 0;
    }
    return 1;
}

int cmmdc(int a, int b)
{
    if(a<0)
        a=-a;
    if(b<0)
        b=-b;

    while(a!=b)
    {
        if(a>b)
            a=a-b;
        else
            b=b-a;
    }
    return a;
}

//int putere(int a,int b)
//{
//    int z=a;
//    for(int i=1;i<=b-1;i++)
//        z*=a;
//}

Monom::Monom()
{
    grad = 0;
    coef = 0;
}

Monom::Monom(int newGrad, int newCoef)
{
  grad = newGrad;
  coef = newCoef;
}

Monom::Monom(const Monom& m)
{
    grad = m.grad;
    coef = m.coef;
}

Monom::~Monom()
{
}

const Monom& Monom::operator=(const Monom& m)
{
  if (this != &m)
  {
      grad = m.grad;
      coef = m.coef;
  }

  return *this;
}

istream& operator>>(istream& in, Monom& m)
{
    cout << endl << "Dati gradul monomului: ";
    in >> m.grad;

    cout << "Si coeficientul: ";
    in >> m.coef;

    return in;
}

ostream& operator<<(ostream& out, const Monom& m)
{
    if (m.coef == 1)
        out << "+x^" << m.grad;
        else if(m.coef==-1)
        out<<"-x^"<<m.grad;
    else if (m.coef != 0)
    {
        if(m.coef>0)
            out <<"+"<<m.coef << "x^" << m.grad;
        if(m.coef<0)
            out <<m.coef <<"x^"<<m.grad;
    }
    return out;
}

int Monom::getCoef()
{
    return coef;
}

int Monom::getGrad()
{
    return grad;
}
void Monom::setCoef(int value)
{
    coef=value;
}

Polinom::Polinom()
{
    nr_obiecte++;
    nr_monoame = 0;
    m = NULL;
    max_degree=0;
}

Polinom::Polinom(int nr,int degree)
{
    nr_obiecte++;
    nr_monoame = nr;
    max_degree=degree;
    m = new Monom[nr_monoame];
}

Polinom::Polinom(int nr, Monom* m1)
{
    nr_obiecte++;
    nr_monoame = nr;

    m = new Monom[nr_monoame];
    for(int i = 0; i < nr_monoame; i++)
        m[i] = m1[i];
}

Polinom::Polinom(const Polinom& p)
{
    nr_obiecte++;
    nr_monoame = p.nr_monoame;
    max_degree=p.max_degree;
    m = new Monom[nr_monoame];
    for(int i = 0; i < nr_monoame; i++)
        m[i] = p.m[i];
}

Polinom::~Polinom()
{
    nr_obiecte--;
    //cout << endl << "Stergere polinom" << endl;
    delete[] m;
}

int Polinom::getObiect()
{
    return nr_obiecte;
}

void Polinom::setDegree(int k)
{
     max_degree=k;
}

int Polinom::evaluare(int value)
{
    int result=0,temp,power;

    for(int i=0; i<=nr_monoame-1; i++)
    {
        power=1;
        if(m[i].getGrad()>0)
        {

            for(int j=0; j<=m[i].getGrad()-1; j++)
                power*=value;

            temp=m[i].getCoef();
            result+=temp*power;
        }
        if(m[i].getGrad()==0)
        {
            temp=m[i].getCoef();
            result+=temp;
        }
        //power/=value;
    }
    return result;
}

const Polinom& Polinom::operator=(const Polinom& p)
{
   if (this != &p)
   {
      nr_monoame = p.nr_monoame;

      m = new Monom[nr_monoame];
      for(int i = 0; i < nr_monoame; i++)
         m[i] = p.m[i];
   }

   return *this;
}

istream& operator >> (istream& in, Polinom& p)
{
    cout << "DATI POLINOMUL: " << endl << "Numarul de monoame: ";
    in >> p.nr_monoame;

    delete[] p.m;
    p.m = new Monom[p.nr_monoame];
    for(int i = 0; i < p.nr_monoame; i++)
        in >> p.m[i];

    p.max_degree=p.m[0].getGrad();
    cout << endl;
    return in;
}

ostream& operator << (ostream& out, const Polinom& p)
{
    out << endl << "POLINOM: " << endl << "Numarul de monoame: " << p.nr_monoame << endl;
    for (int i = 0; i < p.nr_monoame; i++)
        out << p.m[i];

    out << endl;
    return out;
}


const Polinom_ireductibil& Polinom_ireductibil::operator = (const Polinom_ireductibil& p)
{
    if (this != &p)
   {
      nr_monoame = p.nr_monoame;

      m = new Monom[nr_monoame];
      for(int i = 0; i < nr_monoame; i++)
         m[i] = p.m[i];
   }

   return *this;
}

istream& operator >> (istream& in, Polinom_ireductibil& p)
{
    cout << "DATI POLINOMUL: " << endl << "Numarul de monoame: ";
    in >> p.nr_monoame;

    delete[] p.m;
    p.m = new Monom[p.nr_monoame];
    for(int i = 0; i < p.nr_monoame; i++)
        in >> p.m[i];

    cout << endl;
    return in;
}

ostream& operator << (ostream& out, const Polinom_ireductibil& p)
{
    out << endl << "POLINOM: " << endl << "Numarul de monoame: " << p.nr_monoame << endl;
    for (int i = 0; i < p.nr_monoame; i++)
        out << p.m[i];

    out << endl;
    return out;
}

const Polinom_reductibil& Polinom_reductibil::operator = (const Polinom_reductibil& p)
{
    if (this != &p)
   {
      nr_monoame = p.nr_monoame;

      m = new Monom[nr_monoame];
      for(int i = 0; i < nr_monoame; i++)
         m[i] = p.m[i];
   }

   return *this;
}

istream& operator >> (istream& in, Polinom_reductibil& p)
{
    cout << "DATI POLINOMUL: " << endl << "Numarul de monoame: ";
    in >> p.nr_monoame;

    delete[] p.m;
    p.m = new Monom[p.nr_monoame];
    for(int i = 0; i < p.nr_monoame; i++)
        in >> p.m[i];

    cout << endl;
    return in;
}

ostream& operator << (ostream& out, const Polinom_reductibil& p)
{
    out << endl << "POLINOM: " << endl << "Numarul de monoame: " << p.nr_monoame << endl;
    for (int i = 0; i < p.nr_monoame; i++)
        out << p.m[i];

    out << endl;
    return out;
}

bool Polinom::verifica()
{
    int aux,ok=0,cmmdc1,temp,max_coef=0,primulCoeficient=m[0].getCoef();

    for(int i=1; i<=nr_monoame-1; i++)
    {
        temp=m[i].getCoef();
        if(temp!=primulCoeficient)
        {
            ok=1;
            break;
        }
    }

    for(int i=0; i<=nr_monoame; i++)
    {
        if(m[i].getCoef()==1 || m[i].getCoef()==-1)
        {
            ok=0;
            break;
        }
    }

    if(ok)
    {
        cmmdc1=cmmdc(m[0].getCoef(),m[1].getCoef());

        if(nr_monoame>=3)
        {
            for(int i=2; i<=nr_monoame-1; i++)
                cmmdc1=cmmdc(cmmdc1,m[i].getCoef());
        }

        if(cmmdc1!=1)
            ok=0;
        else
        {
            for(int i=0; i<nr_monoame; i++)
                if(abs(m[i].getCoef())>max_coef)
                    max_coef=abs(m[i].getCoef());

            aux=2;
            ok=0;
            while(aux<=max_coef/2+1 && ok==0)
            {
                ok=1;
                if(prim(aux))
                {
                    if(m[nr_monoame-1].getCoef()%(aux*aux)!=0)
                    {
                        //cout<<m[nr_monoame-1].getCoef()<<" "<<aux*aux<<endl;
                        for(int j=1; j<=nr_monoame-1; j++)
                            if(m[j].getCoef()%aux!=0)
                            {
                                ok=0;
                                break;
                            }
                        if(m[0].getCoef()%aux==0)
                            ok=0;
                    }
                    else
                        ok=0;

                }
                else
                    ok=0;

                aux++;

                // cout<<ok<<endl;

            }
        }
    }

    if(ok)
        return 1;
    else
        return 0;
}

bool Polinom_ireductibil::verifica()
{


}

bool Polinom_reductibil::verifica()
{
    int termen_liber,ok,divizor=0,v[max_degree],w[nr_monoame+1],nr2,a,b;
    termen_liber=m[nr_monoame-1].getCoef();
//    if(nr_monoame==2 && (m[0].getGrad()==2 && sqrt(m[0].getCoef())==(int)(sqrt(m[0].getCoef()))) && (m[1].getGrad()==1 && sqrt(m[0].getCoef())==(int)(sqrt(m[0].getCoef()))))
//    {
//        ok=1;
//        cout<<"("<<sqrt(m[0].getCoef())<<"*x-"<<sqrt(m[1].getCoef())<<")*("<<sqrt(m[0].getCoef())<<"*x+"<<sqrt(m[1].getCoef())<<")"<<endl;
//
//    }
//    else
    if(m[0].getGrad()==1)
        ok=0;
    else
    {
        if(m[nr_monoame-1].getGrad()>=1)
        {
            ok=1;
            cout<<"x(";
            for(int i=0; i<=nr_monoame-1; i++)
            {
                if(m[i].getCoef()==1)
                    cout<<"+x^"<<m[i].getGrad();
                else if(m[i].getCoef()==-1)
                    cout<<"-x^"<<m[i].getGrad();
                else if(m[i].getCoef()<0)
                cout<<m[i].getCoef()<<"x^"<<m[i].getGrad()-1;
                else if(m[i].getCoef()>0)
                    cout<<"+"<<m[i].getCoef()<<"x^"<<m[i].getGrad()-1;
            }
            cout<<")";
            cout<<endl;
        }
        else
        {

            ok=0;
            int k=abs(termen_liber);

            for(int i=1; i<=k; i++)
            {
                if(k%i==0)
                {
                    //cout<<evaluare(i)<<endl;
                    if(evaluare(i)==0)
                    {

                        ok=1;
                        divizor=i;
                        break;
                    }
                }

                if(k%(-i)==0)
                {
                    //cout<<evaluare(-1)<<endl;
                    if(evaluare(-i)==0)
                    {

                        ok=1;
                        divizor=-i;
                        break;
                    }
                }
            }
            if(ok)
            {
                //cout<<divizor<<endl;
                if(divizor>0)
                    cout<<"(x-"<<divizor<<")(";

                if(divizor<0)
                    cout<<"(x"<<divizor<<")(";

                // cout<<max_degree<<endl;
                for(int i=0; i<=max_degree; i++)
                    v[i]=0;

                int j = 0;
                for(int i=max_degree; i>=0; i--)
                {
                    a=m[j].getGrad();
                    b=m[j].getCoef();

                    if (a == i)
                    {
                        v[a]=b;
                        j++;
                    }
                }
            }
//
//                for(int i=0; i<=max_degree;i++)
//                    cout<<v[i]<<" ";
//                cout<<endl;
            if(ok==1)
            {

                w[0]=divizor;
                w[1]=v[max_degree];

                int a=divizor,b;
                nr2=max_degree-1;
                for(int i=1; i<=max_degree-1; i++)
                {
                    b=w[i];
                    w[i+1]=a*b+v[nr2-i+1];

                }

//                for(int i=1; i<=max_degree; i++)
//                    cout<<w[i]<<" ";
//                    cout<<endl;

                int grad=max_degree-1;

                for(int i=1; i<=max_degree; i++)
                {
                    if(w[i]==1)
                    {
                        cout<<"x^"<<grad;
                        grad--;
                    }
                    if(w[i]==-1)
                    {
                        cout<<"-x^"<<grad;
                        grad--;
                    }
                    if(w[i]>1)
                    {
                        cout<<"+"<<w[i]<<"x^"<<grad;
                        grad--;
                    }
                       if(w[i]<-1)
                    {
                        cout<<w[i]<<"x^"<<grad;
                        grad--;
                    }
                    if(w[i]==0)
                        grad--;
                }
                cout<<")";
            }
        }
    }
    if(ok==0)
        return 0;

    return 1;

}



