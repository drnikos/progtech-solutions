#include <bits/stdc++.h>
using namespace std;

class lexicon {
public:
  lexicon();
  ~lexicon();

  void insert(const string &s);
  int lookup(const string &s) const;
  int depth(const string &s);
  void replace(const string &s1, const string &s2);

  friend ostream &operator<<(ostream &out, const lexicon &l);

private:
  struct Node {
    string word;
    int times;
    Node *left;
    Node *right;
    Node(string s, Node *l = nullptr, Node *r = nullptr)
        : word(s), left(l), right(r), times(1) {}
  };
  Node *root;
  static Node *remover(Node *n, const string &word) {
    if (n == nullptr)
      return n;
    if (word < n->word)
      n->left = remover(n->left, word);
    else if (word > n->word)
      n->right = remover(n->right, word);
    else {
      if (n->left == nullptr && n->right == nullptr) {
        delete n;
        return nullptr;
      } else if (n->left == nullptr) {
        Node *temp = n->right;
        delete n;
        return temp;
      } else if (n->right == nullptr) {
        Node *temp = n->left;
        delete n;
        return temp;
      }
      Node *temp = maxValueNode(n->left);
      n->word = temp->word;
      n->times = temp->times;
      n->left = remover(n->left, temp->word);
    }
    return n;
  }
  static Node *maxValueNode(Node *n) {
    while (n->right != nullptr)
      n = n->right;
    return n;
  }
  void printer(Node *n) const;
  void destructor(Node *n);
};

lexicon::lexicon() : root(nullptr) {}
lexicon::~lexicon() { destructor(root); }
void lexicon::insert(const string &s) {
  if (root == nullptr) {
    root = new Node(s);
    return;
  }
  Node *current = root;
  Node *parent = nullptr;
  while (current != nullptr) {
    if (current->word == s) {
      current->times++;
      return;
    }
    parent = current;
    if (s < current->word) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  if (s < parent->word) {
    parent->left = new Node(s);
  } else {
    parent->right = new Node(s);
  }
}
int lexicon::lookup(const string &s) const {
  Node *temp = root;
  while (temp != nullptr) {
    if (temp->word == s) {
      return temp->times;
    }
    if (temp->word > s) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }
  return 0;
}
int lexicon::depth(const string &s) {
  int depth = -1;
  Node *temp = root;
  while (temp != nullptr) {
    depth++;
    if (temp->word > s) {
      temp = temp->left;
    } else if (temp->word < s)
      temp = temp->right;

    else
      return depth;
  }
  return -1;
}
void lexicon::replace(const string &s1, const string &s2) {
  if (lookup(s1) == 0)
    return;
  int new_times = lookup(s1) + lookup(s2);
  root = remover(root, s1);
  insert(s2);
  Node *temp = root;
  while (s2 != temp->word) {
    if (s2 > temp->word)
      temp = temp->right;
    else if (s2 < temp->word)
      temp = temp->left;
  }
  temp->times = new_times;
}
void lexicon::destructor(Node *n) {
  if (n != nullptr) {
    destructor(n->left);
    destructor(n->right);
    delete n;
  }
}

void lexicon::printer(Node *n) const {
  if (n != nullptr) {
    printer(n->left);
    cout << n->word << " " << n->times << endl;
    printer(n->right);
  }
}
ostream &operator<<(ostream &out, const lexicon &l) {
  l.printer(l.root);
  return out;
}

#ifndef CONTEST
int main() {
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
