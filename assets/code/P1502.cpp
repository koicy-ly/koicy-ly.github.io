/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Apparition (n@rbtr.ee)
 * DO OR DIE
 */

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define AS 3 +

using namespace std;
using tp = long long;

constexpr tp Hat_N = 1e4;

tp r[AS 2 * Hat_N], mav[AS 8 * Hat_N], delay[AS 8 * Hat_N];

struct Line {
  tp x, s, e, d;

  Line() = default;
  Line(tp _x, tp _s, tp _e, tp _d) : x(_x), s(_s), e(_e), d(_d) {}

  bool operator<(const Line& comp) const {
    if (x == comp.x) return d > comp.d;
    return x < comp.x;
  }
} l[AS 2 * Hat_N];

void pushdown(tp x, tp l, tp r) {
  mav[x] += delay[x];
  if (l != r) {
    delay[x << 1] += delay[x];
    delay[x << 1 | 1] += delay[x];
  }
  delay[x] = 0;
}

void modify(tp x, tp l, tp r, tp ml, tp mr, tp d) {
  if (ml <= l && r <= mr) return delay[x] += d, void();
  else {
    tp mid = l + r >> 1;
    if (ml <= mid) modify(x << 1, l, mid, ml, mr, d);
    if (mid < mr) modify(x << 1 | 1, mid + 1, r, ml, mr, d);
    pushdown(x << 1, l, mid);
    pushdown(x << 1 | 1, mid + 1, r);
    mav[x] = max(mav[x << 1], mav[x << 1 | 1]);
  }
}

signed main() {
  tp t;
  scanf("%lld", &t);
  while (t--) {
    tp n, w, h, tar = 0;
    scanf("%lld%lld%lld", &n, &w, &h);
    memset(mav, 0, sizeof mav);
    memset(delay, 0, sizeof delay);
    for (tp i = 1; i <= n; ++i) {
      tp x, y, c;
      scanf("%lld%lld%lld", &x, &y, &c);
      l[i] = Line(x, y, y + h - 1, c);
      l[i + n] = Line(x + w- 1, y, y + h - 1, -c);
      r[i] = y + h - 1;
      r[i + n] = y;
    }
    n *= 2;
    stable_sort(l + 1, l + n + 1);
    stable_sort(r + 1, r + n + 1);
    for (tp i = 1, m = unique(r + 1, r + n + 1) - r; i <= n; ++i) {
      tp s = lower_bound(r + 1, r + m, l[i].s) - r,
         e = lower_bound(r + 1, r + m, l[i].e) - r;
      modify(1, 1, m - 1, s, e, l[i].d);
      tar = max(tar, mav[1]);
    }
    printf("%lld
", tar);
  }
  return 0;
}

//*/
