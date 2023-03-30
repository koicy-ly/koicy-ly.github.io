/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Spectre (v@rbtr.ee)
 * DO OR DIE
 */

#include <iostream>

using namespace std;
typedef long long tp;

constexpr tp Hat_N = 403, MOD = 1e9 + 7;

tp v[Hat_N][Hat_N * 2];

tp qpow(tp x, tp y, tp z) {
  tp tar = 1;
  while (y) {
    if (y & 1) tar = tar * x % z;
    x = x * x % z;
    y /= 2;
  }
  return tar;
}

signed main() {
  tp n;
  cin >> n;
  for (tp i = 1; i <= n; ++i) {
    for (tp j = 1; j <= n; ++j) {
      cin >> v[i][j];
      v[i][i + n] = 1;
    }
  }
  for (tp i = 1; i <= n; ++i) {
    tp loc = i, inv;
    for (tp j = i + 1; j <= n; ++j) {
      if (v[j][i] > v[loc][i]) loc = j;
    }
    swap(v[i], v[loc]);
    if (!v[i][i]) {
      puts("No Solution");
      return 0;
    }
    inv = qpow(v[i][i], MOD - 2, MOD);
    for (tp j = 1; j <= n; ++j) {
      if (i != j) {
        for (tp p = v[j][i] * inv % MOD, k = i, endk = n << 1; k <= endk; ++k)
          v[j][k] = ((v[j][k] - v[i][k] * p) % MOD + MOD) % MOD;
      }
    }
    for (tp j = 1, endj = n * 2; j <= endj; ++j) v[i][j] = v[i][j] * inv % MOD;
  }
  for (tp i = 1; i <= n; ++i) {
    for (tp j = n + 1, endj = n * 2; j <= endj; ++j)
      cout << v[i][j] << " 
"[j == endj];
  }
  return 0;
}

//*/
