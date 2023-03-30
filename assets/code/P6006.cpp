/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Apparition (n@rbtr.ee)
 * DO OR DIE
 */

#include <cstdio>
#include <unordered_map>
#define AS 3 +

using namespace std;
using tp = long long;

constexpr tp Hat_N = 5000;

tp s[AS Hat_N];
tp cnt[AS Hat_N][AS Hat_N];

signed main() {
  tp n, m;
  scanf("%lld%lld", &n, &m);
  for (tp i = 1; i <= n; ++i) scanf("%lld", s + i);
  for (tp i = 1; i < n; ++i) {
    unordered_map<tp, tp> c;
    c.reserve(n - i);
    for (tp j = i + 1; j <= n; ++j) {
      if (c.count(-s[i] - s[j])) cnt[i][j] = c[-s[i] - s[j]];
      ++c[s[j]];
    }
  }
  for (tp i = n; i >= 1; --i) {
    for (tp j = 1; j <= n; ++j)
      cnt[i][j] += cnt[i + 1][j] + cnt[i][j - 1] - cnt[i + 1][j - 1];
  }
  while (m--) {
    tp l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld
", cnt[l][r]);
  }
  return 0;
}

//*/