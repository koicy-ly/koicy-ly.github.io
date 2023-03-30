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

constexpr tp Hat_N = 1e5 + 3;

vector<tp> e[Hat_N];

tp a[Hat_N], hson[Hat_N], dep[Hat_N], fa[Hat_N], ts[Hat_N], id[Hat_N],
   real[Hat_N], top[Hat_N], sum[Hat_N * 4], col[Hat_N], delay[Hat_N * 4];

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
  col[nid] = a[x];
  if (!hson[x]) return;
  tag(hson[x], f);
  for (auto&& i : e[x]) {
    if (i != fa[x] && i != hson[x]) tag(i, i);
  }
}

void build(tp x, tp l, tp r) {
  if (l == r) {
    return sum[x] = 1, void();
  } else {
    tp mid = l + r >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    sum[x] = sum[x << 1] + sum[x << 1 | 1] - (col[mid] == col[mid + 1]);
  }
}

void pushdown(tp x, tp mid) {
  if (delay[x]) {
    delay[x << 1] = delay[x << 1 | 1] = col[mid] = col[mid + 1] = delay[x];
    sum[x << 1] = sum[x << 1 | 1] = 1;
    delay[x] = 0;
  }
}

void modify(tp x, tp l, tp r, tp ml, tp mr, tp d) {
  if (l >= ml && r <= mr) {
    sum[x] = 1;
    return delay[x] = col[l] = col[r] = d, void();
  } else {
    tp mid = l + r >> 1;
    pushdown(x, mid);
    if (mid >= ml) modify(x << 1, l, mid, ml, mr, d);
    if (mid < mr) modify(x << 1 | 1, mid + 1, r, ml, mr, d);
    sum[x] = sum[x << 1] + sum[x << 1 | 1] - (col[mid] == col[mid + 1]);
  }
}

tp query(tp x, tp l, tp r, tp ml, tp mr) {
  if (l >= ml && r <= mr) return sum[x];
  else {
    tp mid = l + r >> 1, sum = 0;
    pushdown(x, mid);
    if (mid >= ml) sum = query(x << 1, l, mid, ml, mr);
    if (mid < mr) sum += query(x << 1 | 1, mid + 1, r, ml, mr);
    return sum - (mid >= ml && mid < mr && col[mid] == col[mid + 1]);
  }
}

void op1(tp x, tp y, tp z) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    modify(1, 1, n, id[top[x]], id[x], z);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  modify(1, 1, n, id[x], id[y], z);
}

tp op2(tp x, tp y) {
  tp u = x, v = y, acc = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    acc += query(1, 1, n, id[top[x]], id[x]);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  acc += query(1, 1, n, id[x], id[y]);
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    acc -= col[id[top[u]]] == col[id[fa[top[u]]]];
    u = fa[top[u]];
  }
  return acc;
}

signed main() {
  tp m;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (tp i = 1; i <= n; ++i) cin >> a[i];
  for (tp i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  sub(1, 1);
  tag(1, 1);
  build(1, 1, n);
  while (m--) {
    char op;
    tp x, y;
    cin >> op >> x >> y;
    if (op == 'C') {
      tp c;
      cin >> c;
      op1(x, y, c);
    } else cout << op2(x, y) << '\n';
  }
  return 0;
}

//*/
