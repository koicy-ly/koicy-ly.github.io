// 488827
#include <iostream>
#include <vector>

using namespace std;
using Pii = pair<int, int>;

const int kN = 2e5 + 1;

struct I {
  int s, mx, mn;

  I(int s = 0, int mx = -1e9, int mn = 1e9) : s(s), mx(mx), mn(mn) {}
  I operator+(const I &o) const { return I(s + o.s, max(mx, o.mx), min(mn, o.mn)); }
  void operator+=(bool o) { o && (s *= -1, swap(mx, mn), mx *= -1, mn *= -1); }
} ei[kN << 2];
int n, q, fa[kN], de[kN], od[kN], oc, sz[kN], hs[kN], tp[kN], a[kN], na[kN], ete[kN];
bool et[kN << 2];
vector<pair<Pii, int>> e[kN];

void D(int x, int f) {
  fa[x] = f, de[x] = de[f] + 1, sz[x] = 1;
  for (auto [i, j] : e[x]) {
    if (i.first != f) {
      D(i.first, x), a[i.first] = i.second, ete[j] = i.first, sz[x] += sz[i.first];
      hs[x] = max(i.first, hs[x], [](int i, int j) { return sz[i] < sz[j]; });
    }
  }
}
void C(int x, int t) {
  na[od[x] = ++oc] = a[x], tp[x] = t, hs[x] && (C(hs[x], t), 0);
  for (auto [i, j] : e[x]) {
    if (i.first != fa[x] && i.first != hs[x]) {
      C(i.first, i.first);
    }
  }
}
void B(int x, int l, int r) {
  if (l == r) {
    ei[x].s = ei[x].mx = ei[x].mn = na[l];
    return;
  }
  int m = l + r >> 1;
  B(x * 2, l, m), B(x * 2 + 1, m + 1, r);
  ei[x] = ei[x * 2] + ei[x * 2 + 1];
}
void T(int x, bool v) { ei[x] += v, et[x] ^= v; }
I G(int x, int l, int r, int tl, int tr, bool v) {
  if (l == tl && r == tr) {
    return ei[x] += v, et[x] ^= v, ei[x];
  }
  T(x * 2, et[x]), T(x * 2 + 1, et[x]), et[x] = 0;
  int m = l + r >> 1;
  I s;
  if (tl <= m) {
    s = s + G(x * 2, l, m, tl, min(m, tr), v);
  }
  if (m < tr) {
    s = s + G(x * 2 + 1, m + 1, r, max(m + 1, tl), tr, v);
  }
  ei[x] = ei[x * 2] + ei[x * 2 + 1];
  return s;
}
void C(int x, int l, int r, int t, int v) {
  if (l == r) {
    ei[x].s = ei[x].mx = ei[x].mn = v;
    return;
  }
  T(x * 2, et[x]), T(x * 2 + 1, et[x]), et[x] = 0;
  int m = l + r >> 1;
  C(x * 2 + (m < t), t <= m ? l : m + 1, t <= m ? m : r, t, v);
  ei[x] = ei[x * 2] + ei[x * 2 + 1];
}
I OC(int x, int y, bool v) {
  I s;
  for (; tp[x] != tp[y]; x = fa[tp[x]]) {
    de[tp[x]] < de[tp[y]] && (swap(x, y), 0), s = s + G(1, 1, n, od[tp[x]], od[x], v);
  }
  if (x != y) {
    de[x] < de[y] && (swap(x, y), 0), s = s + G(1, 1, n, od[y] + 1, od[x], v);
  }
  return s;
}

int main() {
  cin >> n;
  for (int i = 1, x, y, w; i < n; ++i) {
    cin >> x >> y >> w, ++x, ++y;
    e[x].push_back({{y, w}, i}), e[y].push_back({{x, w}, i});
  }
  D(1, 0), C(1, 1), B(1, 1, n);
  for (cin >> q; q--; ) {
    string o;
    int x, y;
    cin >> o >> x >> y, ++x, ++y;
    if (o == "C") {
      C(1, 1, n, od[ete[x - 1]], y - 1);
    } else if (o == "N") {
      OC(x, y, 1);
    } else {
      I s = OC(x, y, 0);
      if (o == "SUM") {
        cout << s.s << '\n';
      } else if (o == "MAX") {
        cout << s.mx << '\n';
      } else {
        cout << s.mn << '\n';
      }
    }
  }
  return 0;
}