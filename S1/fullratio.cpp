#ifndef CONTEST
#include "fullratio.hpp"
#endif
#include <iostream>

rational::rational(int a, int b) {
    int g = gcd(a, b);
    nom = a / g;
    den = b / g;
}

rational operator+(const rational &x, const rational &y) {
    int n_nom = x.nom * y.den + x.den * y.nom;
    int n_den = x.den * y.den;
    int g = rational::gcd(n_den, n_nom);
    n_nom /= g;
    n_den /= g;
    return {n_nom, n_den};
}
rational operator-(const rational &x, const rational &y) {
    int n_nom = x.nom * y.den - x.den * y.nom;
    int n_den = x.den * y.den;
    int g = rational::gcd(n_den, n_nom);
    n_nom = n_nom / g;
    n_den = n_den / g;
    return {n_nom, n_den};
}
rational operator*(const rational &x, const rational &y) {
    int g = rational::gcd(x.nom * y.nom, x.den * y.den);
    return {x.nom * y.nom / g, x.den * y.den / g};
}
rational operator/(const rational &x, const rational &y) {
    int g = rational::gcd(x.nom * y.den, x.den * y.nom);
    return {x.nom * y.den / g, x.den * y.nom / g};
}
std::ostream &operator<<(std::ostream &out, const rational &x) {
    out << x.nom << "/" << x.den;
    return out;
}


int rational::gcd(int a, int b) {
    int res = std::min(a, b);
    while (res > 1) {
        if (a % res == 0 && b % res == 0)
            break;
        res--;
    }
    return res;
}
