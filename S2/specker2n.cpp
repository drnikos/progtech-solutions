#ifndef CONTEST
#include "specker1n.cpp"
#endif

#include <bits/stdc++.h>
using namespace std;

class Player {
public:
  Player(const string &n) : name(n) {}
  virtual ~Player() {}
  virtual const string &getType() const = 0;
  virtual Move play(const State &s) = 0;
  friend ostream &operator<<(ostream &out, const Player &player) {
    out << player.type << " player " << player.name;
    return out;
  }

protected:
  string name, type;
};

class GreedyPlayer : public Player {
public:
  GreedyPlayer(const string &n) : Player(n) { type = "Greedy"; }
  const string &getType() const override { return type; }
  Move play(const State &s) override {
    int maxh = 0, maxcoins = 0;
    for (int i = 0; i < s.getHeaps(); i++) {
      int x = s.getCoins(i);
      if (x > maxcoins) {
        maxcoins = x;
        maxh = i;
      }
    }
    return Move(maxh, maxcoins, 0, 0);
  }
};

class SpartanPlayer : public Player {
public:
  SpartanPlayer(const string &n) : Player(n) { type = "Spartan"; }
  const string &getType() const override { return type; }
  Move play(const State &s) override {
    int maxh = 0, maxcoins = 0;
    for (int i = 0; i < s.getHeaps(); i++) {
      int x = s.getCoins(i);
      if (x > maxcoins) {
        maxcoins = x;
        maxh = i;
      }
    }
    return Move(maxh, 1, 0, 0);
  }
};

class SneakyPlayer : public Player {
public:
  SneakyPlayer(const string &n) : Player(n) { type = "Sneaky"; }
  const string &getType() const override { return type; }
  Move play(const State &s) override {
    int minh = 0, mincoins = INT_MAX;
    for (int i = 0; i < s.getHeaps(); i++) {
      int x = s.getCoins(i);
      if (x < mincoins && x > 0) {
        mincoins = x;
        minh = i;
      }
    }
    return Move(minh, mincoins, 0, 0);
  }
};

class RighteousPlayer : public Player {
public:
  RighteousPlayer(const string &n) : Player(n) { type = "Righteous"; }
  const string &getType() const override { return type; }
  Move play(const State &s) override {
    int maxh = 0, maxcoins = 0, minh = 0, mincoins = INT_MAX;
    for (int i = 0; i < s.getHeaps(); i++) {
      int x = s.getCoins(i);
      if (x > maxcoins) {
        maxcoins = x;
        maxh = i;
      }
      if (x < mincoins) {
        mincoins = x;
        minh = i;
      }
    }
    int half = maxcoins % 2 == 0 ? maxcoins / 2 : (maxcoins / 2) + 1;
    return Move(maxh, half, minh, half - 1);
  }
};
