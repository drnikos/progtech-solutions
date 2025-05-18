#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
  int V;
  vector<vector<int>> adj;

  Graph(int V) : V(V), adj(V) {}

  void addEdge(int u, int v) { adj[u].push_back(v); }

  bool dfs(int u, vector<int> &state, vector<int> &parent, int &cycle_start,
           int &cycle_end) const {
    state[u] = 1;
    for (int v : adj[u]) {
      if (state[v] == 0) {
        parent[v] = u;
        if (dfs(v, state, parent, cycle_start, cycle_end))
          return true;
      } else if (state[v] == 1) {
        cycle_start = v;
        cycle_end = u;
        return true;
      }
    }
    state[u] = 2;
    return false;
  }

  bool cycle(vector<int> &path) const {
    vector<int> state(V, 0), parent(V, -1);
    int cycle_start = -1, cycle_end = -1;

    for (int u = 0; u < V; ++u) {
      if (state[u] == 0) {
        if (dfs(u, state, parent, cycle_start, cycle_end)) {
          path.clear();
          path.push_back(cycle_start);
          for (int v = cycle_end; v != cycle_start; v = parent[v])
            path.push_back(v);
          path.push_back(cycle_start);
          reverse(path.begin(), path.end());
          path.pop_back();
          return true;
        }
      }
    }
    return false;
  }
};