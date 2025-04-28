#include <bits/stdc++.h>
using namespace std;

struct Node
{
  string data;
  int times;
  Node *left, *right;
  Node(string s, Node *l = nullptr, Node *r = nullptr) : data(s), left(l), right(r), times(1) {}
};

class lexicon
{
public:
  lexicon();
  ~lexicon();

  void insert(const string &s);
  int lookup(const string &s) const;
  int depth(const string &s);
  void replace(const string &s1, const string &s2);

  friend ostream &operator<<(ostream &out, const lexicon &l);

private:
  Node *r;
  void katastrofeas(Node *p);
  void afaireths(const string &s);
  void printer(ostream &out, Node *n) const;
};

lexicon::lexicon() : r(nullptr) {}
lexicon::~lexicon() { katastrofeas(r); }
void lexicon::insert(const string &s)
{
  if (r == nullptr)
  {
    r = new Node(s);
    return;
  }
  Node *temp = r;
  while (s != temp->data)
  {
    if (s > temp->data)
    {
      if (temp->right != nullptr)
        temp = temp->right;
      else
      {
        temp->right = new Node(s);
        return;
      }
    }
    else if (s < temp->data)
    {
      if (temp->left != nullptr)
        temp = temp->left;
      else
      {
        temp->left = new Node(s);
        return;
      }
    }
  }
  temp->times++;
  return;
}
int lexicon::lookup(const string &s) const
{
  Node *temp = r;
  while (temp != nullptr)
  {
    if (s == temp->data)
      return temp->times;
    else
    {
      if (s < temp->data)
        temp = temp->left;
      else if (s > temp->data)
        temp = temp->right;
    }
  }
  return 0;
}
int lexicon::depth(const string &s)
{
  Node *temp = r;
  int counter = 0;
  while (temp != nullptr)
  {
    if (s == temp->data)
      return counter;

    if (s < temp->data)
      temp = temp->left;
    else if (s > temp->data)
      temp = temp->right;
    counter++;
  }
  return -1;
}
void lexicon::replace(const string &s1, const string &s2)
{
  int x = lookup(s1);
  if (x == 0)
    return;
  int res_ties = x + lookup(s2);
  afaireths(s1);
  afaireths(s2);
  insert(s2);
  Node *temp = r;
  while (s2 != temp->data)
  {
    if (s2 > temp->data)
      temp = temp->right;
    else if (s2 < temp->data)
      temp = temp->left;
  }
  temp->times = res_ties;
}
ostream &operator<<(ostream &out, const lexicon &l)
{
  l.printer(out, l.r);
  return out;
}
void lexicon::printer(ostream &out, Node *n) const
{
  if (n != nullptr)
  {
    printer(out, n->left);
    out << n->data << " " << n->times << "\n";
    printer(out, n->right);
  }
}
void lexicon::katastrofeas(Node *p)
{
  if (p != nullptr)
  {
    katastrofeas(p->left);
    katastrofeas(p->right);
    delete p;
  }
}
void lexicon::afaireths(const string &s)
{
  Node *n = r;
  Node *parent = nullptr;

  while (n != nullptr && n->data != s)
  {
    parent = n;
    if (s < n->data)
      n = n->left;
    else
      n = n->right;
  }

  if (n == nullptr) // Node not found
    return;

  if (n->left == nullptr && n->right == nullptr) // Leaf node
  {
    if (n == r)
      r = nullptr;
    else if (parent->left == n)
      parent->left = nullptr;
    else
      parent->right = nullptr;
    delete n;
  }
  else if (n->left == nullptr) // Node with only right child
  {
    if (n == r)
      r = n->right;
    else if (parent->left == n)
      parent->left = n->right;
    else
      parent->right = n->right;
    delete n;
  }
  else if (n->right == nullptr) // Node with only left child
  {
    if (n == r)
      r = n->left;
    else if (parent->left == n)
      parent->left = n->left;
    else
      parent->right = n->left;
    delete n;
  }
  else // Node with two children
  {
    Node *successorParent = n;
    Node *successor = n->right;

    while (successor->left != nullptr)
    {
      successorParent = successor;
      successor = successor->left;
    }

    n->data = successor->data;
    n->times = successor->times;

    if (successorParent->left == successor)
      successorParent->left = successor->right;
    else
      successorParent->right = successor->right;

    delete successor;
  }
}

#ifndef CONTEST
int main()
{
  lexicon l;
  l.insert("the");
  l.insert("boy");
  l.insert("and");
  l.insert("the");
  l.insert("wolf");
  cout << "The word 'the' is found " << l.lookup("the") << " time(s)" << endl;
  cout << "The word 'and' is found at depth " << l.depth("and") << endl;
  cout << l;
  l.replace("boy", "wolf");
  cout << "After replacement:\n";
  cout << l;
  cout << "Now the word 'and' is found at depth " << l.depth("and") << endl;
}
#endif
