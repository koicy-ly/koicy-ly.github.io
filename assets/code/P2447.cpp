/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Spectre (v@rbtr.ee)
 * DO OR DIE
 */

#include <iostream>
#include <bitset>

using namespace std;
typedef long long tp;

constexpr tp Hat_N = 1003, Hat_M = 2003;

bitset<Hat_N> e[Hat_M];

tp GXE(tp n, tp m) {
  tp cnt = -1;
  for (tp i = 1; i <= n; ++i) {
    tp cur = i;
    while (cur <= m && !e[cur][i]) ++cur;
    if (cur > m) return 0;
    cnt = max(cnt, cur);
    if (cur != i) swap(e[cur], e[i]);
    for (tp j = 1; j <= m; ++j) {
      if (i != j && e[j][i]) e[j] ^= e[i];
    }
  }
  return cnt;
}

signed main() {
  tp n, m;
  cin >> n >> m;
  for (tp i = 1, tar; i <= m; ++i) {
    string in;
    cin >> in >> tar;
    for (tp j = 0; j < n; ++j) e[i][j + 1] = in[j] == '1';
    e[i][0] = tar;
  }
  if (tp ret = GXE(n, m)) {
    cout << ret;
    for (tp i = 1; i <= n; ++i) cout << (e[i][0] ? "
?y7M#" : "
Earth");
  } else cout << "Cannot Determine";
  return 0;
}

//*/
