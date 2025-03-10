#include <iostream>  
#ifndef CONTEST  
#include "babyratio.hpp"  
#endif  
  
using namespace std;  
  
rational::rational (int n, int d) {  
  int g = gcd(n, d);  
  nom = n / g;  
  den = d / g;  
}  
  
rational rational::add (rational r) {  
  int a = den * r.nom + nom * r.den;  
  int b = r.den * den;  
  int g = gcd(nom, den);  
  a /= g, b /= g;  
  rational s(a, b);  
  return s;  
}  
  
rational rational::sub (rational r) {  
  int a = nom * r.den - den * r.nom;  
  int b = r.den * den;  
  int g = gcd(nom, den);  
  a /= g, b /= g;  
  rational s(a, b);  
  return s;  
}  
  
rational rational::mul (rational r) {  
  int a = nom * r.nom;  
  int b = r.den * den;  
  int g = gcd(nom, den);  
  a /= g, b /= g;  
  rational s(a, b);  
  return s;  
}  
  
rational rational::div (rational r) {  
  int a = nom * r.den;  
  int b = r.nom * den;  
  int g = gcd(nom, den);  
  a /= g, b /= g;  
  rational s(a, b);  
  return s;  
}  
  
void rational::print () {  
  if (den < 0) nom = (-1) * nom, den = abs(den);  
  std::cout << nom << "/" << den;   
}  
  
int rational::gcd (int a, int b) {  
  a = abs(a), b = abs(b);  
  while (a != 0 && b != 0) {  
    if (a > b) a %= b;  
    else b %= a;  
  }  
  return a+b;  
}