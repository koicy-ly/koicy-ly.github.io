/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Spectre (n@rbtr.ee)
 * DO OR DIE
 */

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long tp;

constexpr tp Hat_N = 1e6 + 3;

struct Line {
  tp l, r, h, d;

  Line() = default;
  Line(tp _l, tp _r, tp _h, tp _d) : l(_l), r(_r), h(_h), d(_d) {}

  bool operator<(const Line& comp) const { return h < comp.h; }
} l[Hat_N * 2];

struct TNode {
  tp sum, len;

  TNode() = default;
} t[Hat_N * 4];

tp y[Hat_N * 2];

void modify(tp x, tp l, tp r, tp ml, tp mr, tp d) {
  if (y[r + 1] <= ml || mr <= y[l]) return;
  if (ml <= y[l] && y[r + 1] <= mr) t[x].sum += d;
  else {
    tp mid = l + r >> 1;
    modify(x << 1, l, mid, ml, mr, d);
    modify(x << 1 | 1, mid + 1, r, ml, mr, d);
  }
  t[x].len = t[x].sum ? y[r + 1] - y[l] : t[x << 1].len + t[x << 1 | 1].len;
}

signed main() {
  tp n, tar = 0;
  cin >> n;
  for (tp i = 1, x1, y1, x2, y2; i <= n; ++i) {
    cin >> x1 >> y1 >> x2 >> y2;
    l[i] = Line(x1, x2, y1, 1);
    l[i + n] = Line(x1, x2, y2, -1);
    y[i] = x1;
    y[i + n] = x2;
  }
  n *= 2;
  stable_sort(l + 1, l + n + 1);
  stable_sort(y + 1, y + n + 1);
  for (tp i = 1, m = unique(y + 1, y + n + 1) - y - 2; i < n; ++i) {
    modify(1, 1, m, l[i].l, l[i].r, l[i].d);
    tar += t[1].len * (l[i + 1].h - l[i].h);
  }
  cout << tar;
  return 0;
}

//*/
