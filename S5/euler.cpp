#include <bits/stdc++.h>  
int main() {  
  int N, M, u, v;  
  std::cin >> N >> M;  
  std::vector<int> deg(N), odd;  
  for (int i = 0; i < M; ++i, deg[u]++, deg[v]++) std::cin >> u >> v;  
  for (int i = 0; i < N; i++) if (deg[i] % 2) odd.push_back(i);  
  std::cout << (odd.empty() ? "CYCLE" : odd.size() == 2 ? "PATH " + std::to_string(odd[0]) + " " + std::to_string(odd[1]) : "IMPOSSIBLE") << std::endl;  
}  
