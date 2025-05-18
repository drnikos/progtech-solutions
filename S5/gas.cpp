#include <bits/stdc++.h>
using namespace std;

struct State {
  int node, fills, fuel_left;
  vector<int> path;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;
  vector<vector<pair<int, int>>> adj(N);

  for (int i = 0; i < M; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int start, end, cap;
    cin >> start >> end >> cap;

    queue<State> q;
    vector<vector<int>> min_fills(N, vector<int>(cap + 1, INT_MAX));
    q.push({start, 1, cap, {start}});
    min_fills[start][cap] = 1;

    bool found = false;
    vector<int> answer_path;
    int answer_fills = -1;

    while (!q.empty()) {
      State s = q.front();
      q.pop();
      int u = s.node, fills = s.fills, fuel = s.fuel_left;

      if (u == end) {
        found = true;
        answer_path = s.path;
        answer_fills = fills;
        break;
      }

      for (const pair<int, int> &edge : adj[u]) {
        int v = edge.first;
        int d = edge.second;

        if (d > cap)
          continue;

        if (fuel >= d && min_fills[v][fuel - d] > fills) {
          min_fills[v][fuel - d] = fills;
          auto new_path = s.path;
          new_path.push_back(v);
          q.push({v, fills, fuel - d, new_path});
        }
        if (cap >= d && fuel != cap && min_fills[v][cap - d] > fills + 1) {
          min_fills[v][cap - d] = fills + 1;
          auto new_path = s.path;
          new_path.push_back(v);
          q.push({v, fills + 1, cap - d, new_path});
        }
      }
    }

    if (!found) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << "POSSIBLE: " << answer_fills << " fill(s), ";
      for (int i = 0; i < answer_path.size(); ++i) {
        cout << answer_path[i];
        if (i + 1 < answer_path.size())
          cout << " ";
      }
      cout << "\n";
    }
  }
}