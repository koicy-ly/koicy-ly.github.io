// Please submit with C++14! It's best to use C++20 or higher version.
#ifndef LOCAL        // Spectre
#pragma region HEAD  // By rbtree (https://rbtree.dev)
#endif
#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstring>
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
#define ra (scanf("%lld", &la), la)
#define LIKELY(exp) __builtin_expect(bool(exp), 1)
#define UNLIKELY(exp) __builtin_expect(bool(exp), 0)

typedef long long tp;
tp la;
using namespace std;
#ifndef LOCAL
#pragma endregion HEAD
#endif

constexpr bool __MTCS__ = 0;

////////////////////////////////////////////////////////////////////////////////

void __Cored__([[maybe_unused]] tp __TID__) {
  tp n = ra, m = ra, j = 1, c = 0;
  vector<pair<tp, tp>> a(n + 1), b(m + 1);
  multiset<tp> k;
  for (tp i = 1; i <= n; ++i) {
    a[i].second = ra;
    a[i].first = ra;
  }
  for (tp i = 1; i <= m; ++i) {
    b[i].second = ra;
    b[i].first = ra;
  }
  stable_sort(a.begin() + 1, a.end(), greater<pair<tp, tp>>());
  stable_sort(b.begin() + 1, b.end(), greater<pair<tp, tp>>());
  for (tp i = 1; i <= n; ++i) {
    while (j <= m && b[j].first >= a[i].first) {
      k.insert(b[j++].second);
    }
    if (k.lower_bound(a[i].second) == k.end()) {
      puts("-1");
      return;
    }
    c += *k.lower_bound(a[i].second);
    k.erase(k.lower_bound(a[i].second));
  }
  printf("%lld
", c);
}

////////////////////////////////////////////////////////////////////////////////

signed main() {
  static tp __TCS__ = __MTCS__ ? ra : 1, __NOW__ = 0;
  while (__NOW__ < __TCS__) {
    __Cored__(++__NOW__);
  }
  return 0;
}