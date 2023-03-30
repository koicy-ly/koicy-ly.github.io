/*
\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \u2227\uff3f\u2227
\u3000\u3000\u3000\u3000\u3000 \u2227\uff3f\u2227 \u3000\uff08\u00b4<_\uff40 \uff09\u3000 Welcome to My Coding Space ^_^
\u3000\u3000\u3000\u3000 \uff08 \u00b4_\u309d`\uff09\u3000/\u3000 \u2312i
\u3000\u3000\u3000\u3000\uff0f\u3000\u3000\u3000\uff3c\u3000 \u3000  |\u3000|
\u3000\u3000\u3000 /\u3000\u3000 /\uffe3\uffe3\uffe3\uffe3/\u3000|\u3000|
\u3000 \uff3f_(__\uff86\u3064/\u3000\u3000 \u3000 / .| .|\uff3f\uff3f\uff3f\uff3f
\u3000 \u3000\u3000\u3000\uff3c/\uff3f\uff3f\uff3f\uff3f/\u3000\uff08u\u3000\u2283
*/

#include <iostream>

using namespace std;
using tp = int64_t;

namespace Fast_In {
constexpr uintmax_t _Buf_Size = 1ull << 15;
char *buf, *_Start_Iterator, *_End_Iterator;
struct Init {
  Init() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    _Start_Iterator = _End_Iterator = buf = (char*)malloc(_Buf_Size);
  }
  ~Init() { free(buf); }
} Initer;
void fetch(char&);
intmax_t read();
char getcr();
}  // namespace Fast_In
using Fast_In::read, Fast_In::getcr;

signed main(/* >_< */) {
  tp l = read(), r = read();
  if (l == r) {
    for (tp i = 2;; ++i) {
      if (!(l % i)) {
        cout << l / i;
        return 0;
      }
    }
  } else {
    cout << (r & 1 ? r - 1 >> 1 : r >> 1);
  }
  return 0;
}

namespace Fast_In {
void fetch(char& c) {
  if (_Start_Iterator == _End_Iterator) {
    _Start_Iterator = buf;
    _End_Iterator = buf + cin.rdbuf()->sgetn(buf, _Buf_Size);
    if (_Start_Iterator == _End_Iterator) {
      c = -1;
      return;
    }
  }
  c = *_Start_Iterator++;
}

intmax_t read() {
  bool f = 0;
  char c;
  uintmax_t Value = 0;
  for (fetch(c); c > 57 || c < 48; fetch(c)) {
    f |= c == 45;
  }
  while (c < 58 && c > 47) {
    Value += Value << 2;
    Value += Value + (c & 15);
    fetch(c);
  }
  return f ? -Value : Value;
}

char getcr() {
  char c;
  for (fetch(c); c == ' ' || c == '\n' || c == '\r'; fetch(c)) {
  }
  return c;
}
}  // namespace Fast_In

/*#################################################################
#.................................................................#
#.............#......#............Created.By.RBTree...............#
#............#.#....#.#........... Limiting-Factor................#
#.............########............................................#
#............#........#..##############################...........#
#...........#..V....V......#..#........................#..#...#...#
#............#........#....#..........###..###..........#..#.#.#..#
#............#..X##X..#..#............#....#.#...........#..#...#.#
#...........#...N##N...#..#...........###..###..........#.........#
#.......MOO..#..@.....#....#.#.#.#...................#.#..........#
#.............########.....#.#.#.##############.#.#..#.#..........#
#..........................#.#.#.#.............#.#.#.#.#..........#
#......#########...........#.#.#.#.................#.#.#..........#
#.....#.........#..........#.#.#.#.................#.#.#..........#
#.#.#.#G#R#A#S#S#.#.#......#.#.#.#.................#.#.#..........#
#.###################......#.#.#.#.................#.#.#..........#
#...........................#.#.#...................#.#...........#
#.................................................................#
#################################################################*/