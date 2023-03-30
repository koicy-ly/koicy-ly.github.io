/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Apparition (n@rbtr.ee)
 * DO OR DIE
 */

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#define AS 3 +

using namespace std;
using tp = long long;

struct TNode {
  tp key, delay;
  unique_ptr<TNode> l, r;

  TNode() = default;
};

void pushdown(unique_ptr<TNode>& x, tp l, tp r, tp mid) {
  if (l == r) return;
  if (!x->l) x->l = unique_ptr<TNode>(new TNode());
  if (!x->r) x->r = unique_ptr<TNode>(new TNode());
  x->l->key += x->delay * (mid - l + 1);
  x->r->key += x->delay * (r - mid);
  x->l->delay += x->delay;
  x->r->delay += x->delay;
  x->delay = 0;
}

void modify(unique_ptr<TNode>& x, tp l, tp r, tp ml, tp mr, tp d) {
  if (!x) x = unique_ptr<TNode>(new TNode());
  if (ml <= l && r <= mr) {
    x->key += d * (r - l + 1);
    x->delay += d;
  } else {
    tp mid = l + r >> 1;
    pushdown(x, l, r, mid);
    if (mid >= ml) modify(x->l, l, mid, ml, mr, d);
    if (mid < mr) modify(x->r, mid + 1, r, ml, mr, d);
    x->key = x->l->key + x->r->key;
  }
}

tp query(unique_ptr<TNode>& x, tp l, tp r, tp ml, tp mr) {
  if (!x) x = unique_ptr<TNode>(new TNode());
  if (ml <= l && r <= mr) return x->key;
  else {
    tp mid = l + r >> 1, ret = 0;
    pushdown(x, l, r, mid);
    if (mid >= ml) ret += query(x->l, l, mid, ml, mr);
    if (mid < mr) ret += query(x->r, mid + 1, r, ml, mr);
    return ret;
  }
}

signed main() {
  tp n, m;
  unique_ptr<TNode> root(new TNode());
  scanf("%lld%lld", &n, &m);
  for (tp i = 1; i <= n; ++i) {
    tp x;
    scanf("%lld", &x);
    modify(root, 1, n, i, i, x);
  }
  while (m--) {
    tp op, x, y;
    scanf("%lld%lld%lld", &op, &x, &y);
    if (op == 1) {
      tp k;
      scanf("%lld", &k);
      modify(root, 1, n, x, y, k);
    } else printf("%lld
", query(root, 1, n, x, y));
  }
  return 0;
}

//*/