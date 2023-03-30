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

constexpr tp Hat_N = 100003;

tp rec[2][Hat_N];
tp n;

void modifty(tp t, tp loc) {
  while (loc <= n) {
    ++rec[t][loc];
    loc += loc & (~loc + 1);
  }
}

tp query(tp t, tp loc) {
  tp sum = 0;
  while (loc) {
    sum += rec[t][loc];
    loc -= loc & (~loc + 1);
  }
  return sum;
}

signed main() {
  tp m;
  cin >> n >> m;
  while (m--) {
    tp op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      modifty(0, l);
      modifty(1, r);
    } else cout << query(0, r) - query(1, l - 1) << '\n';
  }
  return 0;
}

//*/
