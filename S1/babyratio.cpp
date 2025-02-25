#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>

using namespace std;

rational::rational(const int n, const int d) : nom(n), den(d) {}

rational rational::add(const rational r) const {
    int n_nom = nom * r.den + den * r.nom;
    int n_den = den * r.den;
    int x = gcd(n_den, n_nom);
    n_nom = n_nom / x;
    n_den = n_den / x;
    return rational(n_nom, n_den);
}
rational rational::sub(const rational r) {
    int n_nom = nom * r.den - den * r.nom;
    int n_den = den * r.den;
    int x = gcd(n_den, n_nom);
    n_nom = n_nom / x;
    n_den = n_den / x;
    return {n_nom, n_den};
}
rational rational::mul(const rational r) {
    int x = gcd(nom * r.nom, den * r.den);
    return {nom * r.nom / x, den * r.den / x};
}
rational rational::div(const rational r) {
    int x = gcd(nom * r.den, den * r.nom);
    return {nom * r.den / x, den * r.nom / x};
}

void rational::print() { cout << nom << "/" << den; }
int rational::gcd(int a, int b) {
    a = abs(a), b = abs(b);
    while (a != 0 && b != 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}
