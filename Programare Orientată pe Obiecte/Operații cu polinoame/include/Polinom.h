#include <iostream>
#ifndef POLINOM_H
#define POLINOM_H


class Polinom
{
    private:
        int max_degree;
        double coef[100];

    public:
        Polinom();

        void setCoef(int k, double value);
        void setDegree(int k);
        void citireVector();

        double getCoef(int k);
        int getDegree();
        double evaluate (double value);

        void printPolynomial();

       friend Polinom operator+(Polinom& first_poly,Polinom& second_poly);
	   friend Polinom operator-(Polinom& first_poly,Polinom& second_poly);
	   friend Polinom operator*(Polinom& first_poly,Polinom& second_poly);

        Polinom(const Polinom&);
        ~Polinom();
};

#endif // POLINOM_H
