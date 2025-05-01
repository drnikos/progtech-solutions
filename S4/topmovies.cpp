#include <bits/stdc++.h>
using namespace std;

class TopMovies {
public:
  TopMovies();
  ~TopMovies();
  void insert(const string &title, int vote);
  void print(int howmany);

private:
  map<string, pair<int, int>> movies;
};

TopMovies::TopMovies() {}
TopMovies::~TopMovies() {}
void TopMovies::insert(const string &title, int vote) {
  auto it = movies.find(title);
  if (it == movies.end()) {
    movies[title] = {1, vote};
  } else {
    it->second.first++;
    it->second.second += vote;
  }
}
void TopMovies::print(int howmany) {
  vector<pair<string, int>> movieVotes;
  for (auto &movie : movies) {
    int avgVote = movie.second.second / movie.second.first;
    movieVotes.push_back({movie.first, avgVote});
  }
  sort(movieVotes.begin(), movieVotes.end(),
       [](const pair<string, int> &a, const pair<string, int> &b) {
         if (a.second != b.second)
           return a.second > b.second;
         return a.first < b.first;
       });
  for (int i = 0; i < howmany && i < movieVotes.size(); i++) {
    cout << movieVotes[i].first << " " << movieVotes[i].second << endl;
  }
}
int main() {
  int n;
  cin >> n;
  string title, person;
  int vote;
  TopMovies list;
  while (cin >> title >> person >> vote) {
    if (vote >= 0 && vote <= 100)
      list.insert(title, vote);
  }
  cout << 1 << endl;
  list.print(n);
}
