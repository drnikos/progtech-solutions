#include <bits/stdc++.h>
using namespace std;

class Polynomial {
protected:
  class Term {
  protected:
    int exponent, coefficient;
    Term *next;
    Term(int exp, int coeff, Term *n = nullptr)
        : exponent(exp), coefficient(coeff), next(n) {}
    friend class Polynomial;
    friend ostream &operator<<(ostream &out, const Polynomial &p);
    friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
    friend Polynomial operator*(const Polynomial &p, const Polynomial &q);
  };
  Term *head;

public:
  Polynomial() : head(nullptr) {}
  Polynomial(const Polynomial &p) : head(nullptr) {
    for (Term *t = p.head; t; t = t->next)
      addTerm(t->exponent, t->coefficient);
  }
  ~Polynomial() {
    while (head) {
      Term *temp = head;
      head = head->next;
      delete temp;
    }
  }
  Polynomial &operator=(const Polynomial &p) {
    if (this != &p) {
      this->~Polynomial();
      for (Term *t = p.head; t; t = t->next)
        addTerm(t->exponent, t->coefficient);
    }
    return *this;
  }
  void addTerm(int exp, int coeff) {
    if (coeff == 0)
      return;
    Term **curr = &head;
    while (*curr && (*curr)->exponent > exp)
      curr = &(*curr)->next;
    if (*curr && (*curr)->exponent == exp) {
      (*curr)->coefficient += coeff;
      if ((*curr)->coefficient == 0) {
        Term *temp = *curr;
        *curr = (*curr)->next;
        delete temp;
      }
    } else
      *curr = new Term(exp, coeff, *curr);
  }
  double evaluate(double x) {
    double res = 0;
    for (Term *t = head; t; t = t->next)
      res += t->coefficient * pow(x, t->exponent);
    return res;
  }
  friend Polynomial operator+(const Polynomial &p, const Polynomial &q) {
    Polynomial res = p;
    for (Term *t = q.head; t; t = t->next)
      res.addTerm(t->exponent, t->coefficient);
    return res;
  }
  friend Polynomial operator*(const Polynomial &p, const Polynomial &q) {
    Polynomial res;
    for (Term *t1 = p.head; t1; t1 = t1->next)
      for (Term *t2 = q.head; t2; t2 = t2->next)
        res.addTerm(t1->exponent + t2->exponent,
                    t1->coefficient * t2->coefficient);
    return res;
  }
  friend ostream &operator<<(ostream &out, const Polynomial &p) {
    if (!p.head)
      return out << "0";
    bool first = true;
    for (Term *t = p.head; t; t = t->next) {
      if (!first && t->coefficient > 0)
        out << " + ";
      if (t->coefficient < 0)
        !first ? out << " - " : out << "- ";
      if (abs(t->coefficient) != 1 || t->exponent == 0)
        out << abs(t->coefficient);
      if (t->exponent > 0)
        out << "x";
      if (t->exponent > 1)
        out << "^" << t->exponent;
      first = false;
    }
    return out;
  }
};
#ifndef CONTEST
int main() {
  Polynomial p;
  p.addTerm(1, 3);
  p.addTerm(2, 1);
  p.addTerm(0, -1);
  Polynomial q(p);
  q.addTerm(1, -3);
  cout << "P(x) = " << p << endl;
  cout << "P(1) = " << p.evaluate(1) << endl;
  cout << "Q(x) = " << q << endl;
  cout << "Q(1) = " << q.evaluate(1) << endl;
  cout << "(P + Q)(x) = " << p + q << endl;
  cout << "(P * Q)(x) = " << p * q << endl;
  return 0;
}
#endif
