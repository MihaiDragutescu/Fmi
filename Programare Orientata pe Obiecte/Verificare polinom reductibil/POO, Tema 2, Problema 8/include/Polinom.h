#include <iostream>
#ifndef POLINOM_H
#define POLINOM_H

using namespace std;

class Monom
{
    int grad;
    int coef;

  public:
    Monom();
    Monom(int, int);

    Monom(const Monom&);
    ~Monom();

    int getCoef();
    int getGrad();
    void setCoef(int);

    const Monom& operator=(const Monom&);

    friend istream& operator>>(istream&, Monom&);
    friend ostream& operator<<(ostream&, const Monom&);
};

class Polinom
{
  protected:
    static int nr_obiecte;
    int nr_monoame;
    Monom* m;
    int max_degree;

  public:
    Polinom();
    Polinom(int,int);
    Polinom(int, Monom*);
    Polinom(const Polinom&);
    virtual ~Polinom();

     void setDegree(int);
     int evaluare(int);
     static int getObiect();

    const Polinom& operator = (const Polinom&);
    friend istream& operator >> (istream&, Polinom&);
    friend ostream& operator << (ostream&, const Polinom&);

    virtual bool verifica();
};

class Polinom_ireductibil : public Polinom
{
   public:
       Polinom_ireductibil(int nr, Monom* m): Polinom(nr, m) {}
       Polinom_ireductibil(int nr,int degree): Polinom(nr,degree) {}
       Polinom_ireductibil(const Polinom& p): Polinom(p) {}
       Polinom_ireductibil(const Polinom_ireductibil& pi): Polinom(pi.nr_monoame, pi.m) {}
       ~Polinom_ireductibil() {}

       const Polinom_ireductibil& operator = (const Polinom_ireductibil&);
       friend istream& operator >> (istream&, Polinom_ireductibil&);
       friend ostream& operator << (ostream&, const Polinom_ireductibil&);

       bool verifica();
};

class Polinom_reductibil : public Polinom
{
   public:
       Polinom_reductibil(int nr, Monom* m): Polinom(nr, m) {}
       Polinom_reductibil(int nr,int degree): Polinom(nr,degree) {}
       Polinom_reductibil(const Polinom& p): Polinom(p) {}
       Polinom_reductibil(const Polinom_reductibil& pr): Polinom(pr.nr_monoame, pr.m) {}
       ~Polinom_reductibil() {}

       const Polinom_reductibil& operator = (const Polinom_reductibil&);
       friend istream& operator >> (istream&, Polinom_reductibil&);
       friend ostream& operator << (ostream&, const Polinom_reductibil&);

       bool verifica();
};

#endif // POLINOM_H
