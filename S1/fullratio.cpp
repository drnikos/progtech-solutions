#include <iostream>  
#ifndef CONTEST  
#include "fullratio.hpp"  
#endif  
using namespace std;  
  
rational::rational (int n, int d) {  
  int g = gcd(n, d);  
  nom = n / g;  
  den = d / g;  
}  
  
rational operator + (const rational &x, const rational &y) {  
  int n = y.den * x.nom + y.nom * x.den;  
  int d = x.den * y.den;  
  int g = rational::gcd(n, d);  
  return rational(n / g, d / g);  
}  
rational operator - (const rational &x, const rational &y) {  
  int n = y.den * x.nom - y.nom * x.den;  
  int d = x.den * y.den;  
  int g = rational::gcd(n, d);  
  return rational(n / g, d / g);  
}  
rational operator * (const rational &x, const rational &y) {  
  int n = x.nom * y.nom;  
  int d = x.den * y.den;  
  int g = rational::gcd(n, d);  
  return rational(n / g, d / g);  
}  
rational operator / (const rational &x, const rational &y) {  
  int n = x.nom * y.den;  
  int d = x.den * y.nom;  
  int g = rational::gcd(n, d);  
  return rational(n / g, d / g);  
}  
  
ostream & operator << (std::ostream &out, const rational &x) {  
  int p = x.nom, q = x.den;  
  if (q < 0) p = (-1) * p, q = abs(q);  
  out << p << "/" << q;  
  return out;  
}  
  
int rational::gcd (int a, int b) {  
  a = abs(a), b = abs(b);  
  while (a != 0 && b != 0) {  
    if (a > b) a %= b;  
    else b %= a;  
  }  
  return a+b;  
}