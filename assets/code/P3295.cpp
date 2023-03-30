/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Apparition (n@rbtr.ee)
 * DO OR DIE
 */

#include <algorithm>
#include <cstdio>
#define AS 3 +

using namespace std;
using tp = long long;

constexpr tp Hat_N = 1e5, Hat_F = __lg(Hat_N), c_Mod = 1e9 + 7;

tp f[AS Hat_N][AS Hat_F];

tp find(tp x, tp l) { return f[x][l] == x ? x : f[x][l] = find(f[x][l], l); }

void link(tp x, tp y, tp k) { f[find(x, k)][k] = find(y, k); }

signed main() {
  tp n, m, fl, tar = 0;
  scanf("%lld%lld", &n, &m);
  fl = __lg(n);
  for (tp i = 1; i <= n; ++i) {
    for (tp j = 0; j <= fl; ++j) f[i][j] = i;
  }
  while (m--) {
    tp l1, r1, l2, r2;
    scanf("%lld%lld%lld%lld", &l1, &r1, &l2, &r2);
    for (tp i = fl; i >= 0; --i) {
      if (l1 + (1ll << i) - 1 <= r1) {
        link(l1, l2, i);
        l1 += 1ll << i;
        l2 += 1ll << i;
      }
    }
  }
  for (tp i = fl; i > 0; --i) {
    for (tp j = 1, endj = n + 1 - (1ll << i); j <= endj; ++j) {
      link(find(j, i), j, i - 1);
      link(find(j, i) + (1ll << i - 1), j + (1ll << i - 1), i - 1);
    }
  }
  for (tp i = 1; i <= n; ++i) {
    if (f[i][0] == i) tar = tar ? (tar * 10 % c_Mod) : 9;
  }
  printf("%lld
", tar);
  return 0;
}

//*/