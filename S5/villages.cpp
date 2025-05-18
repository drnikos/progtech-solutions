#include <bits/stdc++.h>
using namespace std;

class UnionFind {
  vector<int> parent, sz;

public:
  UnionFind(int size) {
    parent.resize(size);
    sz.resize(size, 1);
    for (int i = 0; i < size; i++) {
      parent[i] = i;
    }
  }

  int find(int i) {
    if (parent[i] != i) {
      parent[i] = find(parent[i]);
    }
    return parent[i];
  }

  void unite(int i, int j) {
    int irep = find(i);
    int jrep = find(j);
    if (irep != jrep) {
      if (sz[irep] < sz[jrep]) {
        swap(irep, jrep);
      }
      parent[jrep] = irep;
      sz[irep] += sz[jrep];
    }
  }

  bool isRoot(int i) { return parent[i] == i; }
};

int main() {
  ios_base::sync_with_stdio(false);
  int n, m, k;
  cin >> n >> m >> k;
  int a, b;
  UnionFind uf(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    a--;
    b--;
    uf.unite(a, b);
  }

  int components = 0;
  for (int i = 0; i < n; i++) {
    if (uf.find(i) == i) {
      components++;
    }
  }

  int min_teams = max(1, components - k);
  cout << min_teams << endl;
}
