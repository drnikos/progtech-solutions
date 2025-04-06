#include <bits/stdc++.h>
using namespace std;
class ChessBoardArray {
protected:
  class Row {
  public:
    Row(ChessBoardArray &a, int i) : array2D(a), row(i) {}
    int &operator[](int i) const { return array2D.select(row, i); }

  private:
    ChessBoardArray &array2D;
    int row;
  };

  class ConstRow {
  public:
    ConstRow(const ChessBoardArray &a, int i) : array2D(a), row(i) {}
    const int operator[](int i) const { return array2D.select(row, i); }

  private:
    const ChessBoardArray &array2D;
    int row;
  };

  unsigned int loc(int i, int j) const noexcept(false) {
    int di = i - base, dj = j - base;
    if ((di + dj) % 2 != 0 || di < 0 || di >= ncr || dj < 0 || dj >= ncr)
      throw out_of_range("invalid index");
    return (di * ncr + dj) / 2;
  }

  int *data;
  int base;
  int length;
  int ncr;

public:
  ChessBoardArray(unsigned size = 0, unsigned base = 0)
      : base(base), data(new int[(size * size + 1) / 2]()),
        length((size * size + 1) / 2), ncr(size) {}
  ChessBoardArray(const ChessBoardArray &a)
      : base(a.base), data(new int[a.length]), length(a.length), ncr(a.ncr) {
    copy(a.data, a.data + a.length, data);
  };
  ~ChessBoardArray() { delete[] data; }

  ChessBoardArray &operator=(const ChessBoardArray &a) {
    if (this != &a) {
      delete[] data;
      length = a.length;
      base = a.base;
      ncr = a.ncr;
      data = new int[a.length];
      copy(a.data, a.data + a.length, data);
    }
    return *this;
  };

  int &select(int i, int j) { return data[loc(i, j)]; }
  int select(int i, int j) const { return data[loc(i, j)]; };

  const Row operator[](int i) { return Row(*this, i); }
  const ConstRow operator[](int i) const { return ConstRow(*this, i); };

  friend ostream &operator<<(ostream &out, const ChessBoardArray &a) {
    for (auto i = 0; i < a.ncr; i++) {
      for (auto j = 0; j < a.ncr; j++) {
        try {
          out << setw(4) << a.select(i + a.base, j + a.base);
        } catch (out_of_range &e) {
          out << setw(4) << "0";
        }
      }
      out << '\n';
    }
    return out;
  };
};

#ifndef CONTEST
int main() {
  ChessBoardArray a(4, 1);
  a[3][1] = 42;
  a[4][4] = 17;
  try {
    a[2][1] = 7;
  } catch (out_of_range &e) {
    cout << "a[2][1] is black" << endl;
  }
  try {
    cout << a[1][2] << endl;
  } catch (out_of_range &e) {
    cout << "and so is a[1][2]" << endl;
  }
  cout << a;
}
#endif
