#include <iostream>
#include "Polinom.h"

using namespace std;

Polinom::Polinom()
{
    max_degree=0;
    for(int i=0;i<=max_degree;i++)
        coef[i]=0.0;
}

Polinom::Polinom(const Polinom& pol)
{
    max_degree = pol.max_degree;
    for(int i = 0; i <= max_degree; i++)
        coef[i] = pol.coef[i];
}

Polinom::~Polinom()
{
    max_degree = 0;
}

int Polinom::getDegree()
{
    return max_degree;
}

void Polinom::citireVector()
{

}

void Polinom::setDegree(int k)
{
    max_degree = k;
}

double Polinom::getCoef(int k)
{
    if(k<=max_degree)
        return coef[k];
    else
        return 0.0;
}

void Polinom::setCoef(int k,double value)
{
    coef[k]=value;
}

double Polinom::evaluate(double value)
{
    double power=1,result=0;

    for(int i=0;i<=max_degree;i++)
    {
        result+=coef[i]*power;
        power*=value;
    }
    return result;
}

void Polinom::printPolynomial()
{

    for(int i=max_degree;i>=0;i--)
    {
        if(coef[i]>=0)
        {
        if(i==max_degree && coef[i]==1)
            cout<<"x^"<<i;
        if(i==max_degree && coef[i]!=1 && coef[i]!=0)
            cout<<coef[i]<<"*x^"<<i;
        if(i!=max_degree && coef[i]==1)
            cout<<"+x^"<<i;
        if(i!=max_degree && coef[i]!=1 && coef[i]!=0)
            cout<<"+"<<coef[i]<<"*x^"<<i;
        }
        else
        {
        if(i==max_degree && coef[i]==-1)
            cout<<"-x^"<<i;
        if(i==max_degree && coef[i]!=-1 && coef[i]!=0)
            cout<<coef[i]<<"*x^"<<i;
        if(i!=max_degree && coef[i]==-1)
            cout<<"-x^"<<i;
        if(i!=max_degree && coef[i]!=-1 && coef[i]!=0)
            cout<<coef[i]<<"*x^"<<i;
        }
    }
}

Polinom operator+(Polinom& first_poly, Polinom& second_poly)
{
    int first_degree=first_poly.getDegree(),second_degree=second_poly.getDegree(),degree;
    double sum;

    Polinom result;

   if (first_degree > second_degree)
      {
          degree = second_degree;
          result.setDegree(first_degree);
          while (first_degree > second_degree)
          {
              result.setCoef(first_degree, first_poly.getCoef(first_degree));
              first_degree--;
          }
      }
   else
    {
          degree = first_degree;
          result.setDegree(second_degree);
          while (first_degree < second_degree)
          {
              result.setCoef(second_degree, second_poly.getCoef(second_degree));
              second_degree--;
          }
   }

   for (int i=degree; i >= 0; i--)
   {
      sum = first_poly.getCoef(i) + second_poly.getCoef(i);
      if (sum != 0.0)
        result.setCoef(i, sum);
      else
        result.setCoef(i,0);
   }
   return result;
}

Polinom operator-(Polinom& first_poly, Polinom& second_poly)
{
    int first_degree=first_poly.getDegree(),second_degree=second_poly.getDegree(),degree;
    double dif;

    Polinom result;

   if (first_degree > second_degree)
      {
          degree = second_degree;
          result.setDegree(first_degree);
          while (first_degree > second_degree)
          {
              result.setCoef(first_degree, first_poly.getCoef(first_degree));
              first_degree--;
          }
      }
   else
    {
          degree = first_degree;
          result.setDegree(second_degree);
          while (first_degree < second_degree)
          {
              result.setCoef(second_degree, -second_poly.getCoef(second_degree));
              second_degree--;
          }
   }

   for (int i=degree; i >= 0; i--)
   {
      dif = first_poly.getCoef(i) - second_poly.getCoef(i);
      if (dif != 0.0)
        result.setCoef(i, dif);
      else
        result.setCoef(i,0);
   }
   return result;
}

Polinom operator*(Polinom& first_poly, Polinom& second_poly)
{
    int first_degree=first_poly.getDegree(),second_degree=second_poly.getDegree(),degree;
    Polinom result;

    degree=first_degree+second_degree;
    result.setDegree(degree);
    double v[degree];

    for(int i=0;i<=degree;i++)
        v[i]=0;

    for(int i=first_degree;i>=0;i--)
    {
        if(first_poly.getCoef(i)!=0)
        {
            for(int j=second_degree;j>=0;j--)
            {
                if(second_poly.getCoef(j)!=0)
                v[i+j]+=first_poly.getCoef(i)*second_poly.getCoef(j);

            }
        }
    }

    for(int i=degree;i>=0;i--)
        result.setCoef(i,v[i]);

    return result;
}

