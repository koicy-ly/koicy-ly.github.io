// Please submit with C++14!
#pragma region HEAD   // Spectre
#include <algorithm>  // By rbtree (https://rbtree.archi)
#include <array>
#include <bitset>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#ifdef ___RB_DEBUG___
#include "rb_debug.h"
#else
#define dbg(...)
#endif
#define ra (scanf("%lld", &__TEMP_READ_VALUE), __TEMP_READ_VALUE)
#define LIKELY(exp) __builtin_expect(bool(exp), 1)
#define UNLIKELY(exp) __builtin_expect(bool(exp), 0)

typedef long long tp;
tp __TEMP_READ_VALUE;
using namespace std;
#pragma endregion HEAD

////////////////////////////////////////////////////////////////////////////////

signed main() {
  bool f = 1;
  tp n = ra, maxk = ra, lg = ceil(log2(n)), lglg = ceil(log2(lg)), poison = 0;
  array<bitset<1003>, 19> a;
  if (n == 1) {
    puts("2
1");
    return 0;
  }
  for (tp i = 0; i < lg; ++i) {
    tp cnt = 0;
    for (tp j = 0; j < n; ++j) {
      if (j >> i & 1) {
        ++cnt;
        a[i][j] = 1;
      }
    }
    printf("1 %lld", cnt);
    for (tp j = 0; j < n; ++j) {
      if (j >> i & 1) {
        printf(" %lld", j + 1);
      }
    }
    puts("");
  }
  for (tp i = 0; i < lglg; ++i) {
    for (tp j = 0; j < lg; ++j) {
      if (j >> i & 1) {
        a[i + lg] ^= a[j];
      }
    }
    printf("1 %zu", a[i + lg].count());
    for (tp j = 0; j < n; ++j) {
      if (a[i + lg][j]) {
        printf(" %lld", j + 1);
      }
    }
    a[lg + lglg] ^= a[i + lg];
    puts("");
  }
  printf("1 %zu", a[lg + lglg].count());
  for (tp j = 0; j < n; ++j) {
    if (a[lg + lglg][j]) {
      printf(" %lld", j + 1);
    }
  }
  puts("
2");
  fflush(stdout);
  for (tp i = 0; i <= lg + lglg; ++i) {
    a.back()[i] = ra ^ 1;
  }
  for (tp i = lg; i <= lg + lglg; ++i) {
    f ^= a.back()[i];
  }
  if (f) {
    tp mutations = 0;
    for (tp i = 0; i < lglg; ++i) {
      bool g = a.back()[i + lg];
      for (tp j = 0; j < lg; ++j) {
        if (j >> i & 1) {
          g ^= a.back()[j];
        }
      }
      if (g) {
        mutations += 1ll << i;
      }
    }
    a.back()[mutations] = !a.back()[mutations];
  }
  for (tp i = 0; i <= n; ++i) {
    a[17][i] = 1;
  }
  for (tp i = 0; i < lg; ++i) {
    if (a.back()[i]) {
      a[17] &= a[i];
    }
  }
  printf("%zu
", a[17]._Find_first() + 1);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////