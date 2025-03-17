#ifndef CONTEST
#include "specker2n.cpp"
#endif
#include <bits/stdc++.h>
using namespace std;
class Game {
public:
  Game(int heaps, int players);
  ~Game();
  void addHeap(int coins);
  void addPlayer(Player *player);
  void play(ostream &out);
  int getPlayers() const;
  const Player *getPlayer(int p) const;

private:
  int maxheaps, maxplayers, cheaps, cplayers;
  int *coins;
  Player **players;
};
Game::Game(int heaps, int p)
    : maxheaps(heaps), maxplayers(p), cheaps(0), cplayers(0) {
  coins = new int[maxheaps];
  players = new Player *[maxplayers];
}
Game::~Game() {
  delete[] coins;
  for (int i = 0; i < cplayers; ++i) {
    delete players[i];
  }
  delete[] players;
}
void Game::addHeap(int c) {
  if (cheaps >= maxheaps)
    throw std::logic_error("Invalid heap selection");
  coins[cheaps++] = c;
}
void Game::addPlayer(Player *p) {
  if (cplayers >= maxplayers)
    throw std::logic_error("Invalid player selection");
  players[cplayers++] = p;
}
void Game::play(ostream &out) {
  if (cplayers != maxplayers || cheaps != maxheaps)
    throw std::logic_error("Invalid selections");
  else {
    State s(maxheaps, coins, maxplayers);
    while (!s.winning()) {
      out << "State: " << s << endl;
      out << *getPlayer(s.getPlaying()) << " "
          << players[s.getPlaying()]->play(s) << endl;
      s.next(players[s.getPlaying()]->play(s));
    }
    out << "State: " << s << endl;
    int winner = (s.getPlaying() == 0) ? maxplayers - 1 : s.getPlaying() - 1;
    out << *players[winner] << " wins" << endl;
  }
}
int Game::getPlayers() const { return maxplayers; }
const Player *Game::getPlayer(int p) const {
  if (p >= maxplayers || p < 0)
    throw std::logic_error("Invalid player selection");
  return players[p];
}
#ifndef CONTEST
int main() {
  Game specker(3, 4);
  specker.addHeap(10);
  specker.addHeap(20);
  specker.addHeap(17);
  specker.addPlayer(new SneakyPlayer("Tom"));
  specker.addPlayer(new SpartanPlayer("Mary"));
  specker.addPlayer(new GreedyPlayer("Alan"));
  specker.addPlayer(new RighteousPlayer("Robin"));
  specker.play(cout);
}
#endif