#include <bits/stdc++.h>

class Move {
public:
  Move(int sh, int sc, int th, int tc);
  int getSource() const;
  int getSourceCoins() const;
  int getTarget() const;
  int getTargetCoins() const;
  friend std::ostream &operator<<(std::ostream &out, const Move &move);

private:
  int sh, sc, th, tc;
};

class State {
public:
  State(int h, const int c[], int n);
  ~State();
  void next(const Move &move);
  bool winning() const;
  int getHeaps() const;
  int getCoins(int h) const;
  int getPlayers() const;
  int getPlaying() const;
  friend std::ostream &operator<<(std::ostream &out, const State &state);

private:
  int maxheaps;
  int *coins;
  static int players;
  int current_non_zero;
  int current_player;
};

int State::players = 0;

Move::Move(int sh, int sc, int th, int tc) : sh(sh), sc(sc), th(th), tc(tc) {}

int Move::getSource() const { return sh; }
int Move::getSourceCoins() const { return sc; }
int Move::getTarget() const { return th; }
int Move::getTargetCoins() const { return tc; }

std::ostream &operator<<(std::ostream &out, const Move &move) {
  if (move.sc == 0) {
    out << "takes nothing";
    return out;
  }
  if (move.tc != 0)
    out << "takes " << move.sc << " coins from heap " << move.sh << " and puts "
        << move.tc << " coins to heap " << move.th;
  else
    out << "takes " << move.sc << " coins from heap " << move.sh
        << " and puts nothing";
  return out;
}

State::State(int h, const int c[], int n)
    : maxheaps(h), current_non_zero(0), current_player(0) {
  players = n;
  coins = new int[h];
  for (int i = 0; i < h; i++) {
    coins[i] = c[i];
    if (coins[i] > 0)
      current_non_zero++;
  }
}

State::~State() { delete[] coins; }

void State::next(const Move &move) {
  if (move.getSource() < 0 || move.getSource() >= maxheaps ||
      move.getTarget() < 0 || move.getTarget() >= maxheaps) {
    throw std::logic_error("Invalid heap selection");
  }
  if (move.getSourceCoins() > coins[move.getSource()]) {
    throw std::logic_error("Not enough coins in source heap");
  }
  if (move.getTargetCoins() >= move.getSourceCoins()) {
    throw std::logic_error("Cannot transfer more than removed coins");
  }

  coins[move.getSource()] -= move.getSourceCoins();
  if (coins[move.getTarget()] == 0 && move.getTargetCoins() != 0)
    current_non_zero++;
  coins[move.getTarget()] += move.getTargetCoins();

  if (coins[move.getSource()] == 0) {
    current_non_zero--;
  }
  current_player = ((current_player + 1) % players);
}

bool State::winning() const { return current_non_zero == 0; }

int State::getHeaps() const { return maxheaps; }

int State::getCoins(int heap) const {
  if (heap < 0 || heap >= maxheaps) {
    throw std::logic_error("Invalid heap index");
  }
  return coins[heap];
}

int State::getPlayers() const { return players; }

int State::getPlaying() const {
  if (current_player < 0 || current_player >= players) {
    throw std::logic_error("Invalid player turn");
  }
  return current_player;
}

std::ostream &operator<<(std::ostream &out, const State &state) {
  for (int i = 0; i < state.maxheaps - 1; i++)
    out << state.coins[i] << ", ";
  out << state.coins[state.maxheaps - 1];
  out << " with " << state.getPlaying() << "/" << state.getPlayers()
      << " playing next";
  return out;
}
