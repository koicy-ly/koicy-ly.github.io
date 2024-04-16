#include <algorithm>
#include <iostream>
#include <list>

using namespace std;
using tp = int64_t;
constexpr tp Hat_N = 5003;

tp target[Hat_N];
list<tp> l[Hat_N];

signed main() {
  tp n, k;
  cin >> n >> k;
  for (tp i = 1; i <= n; ++i) {
    tp x;
    cin >> x;
    l[x].push_back(i);
  }
  if (max_element(l, l + Hat_N, [](auto& x, auto& y) {
        return x.size() < y.size();
      })->size() > k) {
    puts("NO");
    return 0;
  } else {
    puts("YES");
  }
  for (auto&& i : l) {
    static tp color = 0;
    for (auto&& j : i) {
      target[j] = ++color;
      color %= k;
    }
  }
  for (tp i = 1; i <= n; ++i) {
    cout << target[i] << ' ';
  }
  return 0;
}

/*#################################################################
#.................................................................#
#.............#......#............Created.By.RBTree...............#
#............#.#....#.#...........................................#
#.............########............................................#
#............#........#..##############################...........#
#...........#..V........V..#..#........................#..#...#...#
#............#........#....#..........###..###..........#..#.#.#..#
#............#..X##X..#..#............#....#.#...........#..#...#.#
#...........#...N##N...#..#...........###..###..........#.........#
#.......MOO..#........#....#.#.#.#...................#.#..........#
#.............########.....#.#.#.##############.#.#..#.#..........#
#..........................#.#.#.#.............#.#.#.#.#..........#
#......#########...........#.#.#.#.................#.#.#..........#
#.....#.........#..........#.#.#.#.................#.#.#..........#
#.#.#.#G#R#A#S#S#.#.#......#.#.#.#.................#.#.#..........#
#.###################......#.#.#.#.................#.#.#..........#
#...........................#.#.#...................#.#...........#
#.................................................................#
#################################################################*/