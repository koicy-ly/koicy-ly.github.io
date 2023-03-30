/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Spectre (v@rbtr.ee)
 * DO OR DIE
 */

#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long tp;

constexpr tp Hat_N = 3e4 + 3;

vector<tp> e[Hat_N];

tp a[Hat_N], hson[Hat_N], dep[Hat_N], fa[Hat_N], ts[Hat_N], id[Hat_N],
   real[Hat_N], top[Hat_N], sum[Hat_N << 2], mav[Hat_N << 2];

tp n;

void sub(tp x, tp f) {
  ts[x] = 1;
  dep[x] = dep[fa[x] = f] + 1;
  for (auto&& i : e[x]) {
    if (i != f) {
      sub(i, x);
      ts[x] += ts[i];
      if (ts[i] > ts[hson[x]]) hson[x] = i;
    }
  }
}

void tag(tp x, tp f) {
  static tp nid = 0;
  top[real[id[x] = ++nid] = x] = f;
  if (!hson[x]) return;
  tag(hson[x], f);
  for (auto&& i : e[x]) {
    if (i != fa[x] && i != hson[x]) tag(i, i);
  }
}

void build(tp x, tp l, tp r) {
  if (l == r) return sum[x] = mav[x] = a[real[l]], void();
  build(x << 1, l, l + r >> 1);
  build(x << 1 | 1, l + r + 2 >> 1, r);
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
  mav[x] = max(mav[x << 1], mav[x << 1 | 1]);
}

tp sum_query(tp x, tp l, tp r, tp ml, tp mr) {
  if (l >= ml && r <= mr) return sum[x];
  else {
    tp mid = l + r >> 1, sum = 0;
    if (mid >= ml) sum = sum_query(x << 1, l, mid, ml, mr);
    if (mid < mr) sum += sum_query(x << 1 | 1, mid + 1, r, ml, mr);
    return sum;
  }
}

tp max_query(tp x, tp l, tp r, tp ml, tp mr) {
  if (l >= ml && r <= mr) return mav[x];
  else {
    tp mid = l + r >> 1, mav = -(-1ull >> 1);
    if (mid >= ml) mav = max_query(x << 1, l, mid, ml, mr);
    if (mid < mr) mav = max(mav, max_query(x << 1 | 1, mid + 1, r, ml, mr));
    return mav;
  }
}

void op1(tp x, tp l, tp r, tp u, tp t) {
  if (l == r) return sum[x] = mav[x] = t, void();
  else {
    tp mid = l + r >> 1;
    if (u <= mid) op1(x << 1, l, mid, u, t);
    else op1(x << 1 | 1, mid + 1, r, u, t);
    sum[x] = sum[x << 1] + sum[x << 1 | 1];
    mav[x] = max(mav[x << 1], mav[x << 1 | 1]);
  }
}

tp op2(tp x, tp y) {
  tp acc = -(-1ull >> 1);
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    acc = max(acc, max_query(1, 1, n, id[top[x]], id[x]));
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  return max(acc, max_query(1, 1, n, id[x], id[y]));
}

tp op3(tp x, tp y) {
  tp acc = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    acc += sum_query(1, 1, n, id[top[x]], id[x]);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  return acc + sum_query(1, 1, n, id[x], id[y]);
}

signed main() {
  tp m;
  ios_base::sync_with_stdio(0);
  cin >> n;
  for (tp i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (tp i = 1; i <= n; ++i) cin >> a[i];
  sub(1, 1);
  tag(1, 1);
  build(1, 1, n);
  cin >> m;
  while (m--) {
    tp x, y;
    string op;
    cin >> op >> x >> y;
    if (op == "CHANGE") op1(1, 1, n, id[x], y);
    else if (op == "QMAX") cout << op2(x, y) << '\n';
    else if (op == "QSUM") cout << op3(x, y) << '\n';
  }
  return 0;
}

//*/
