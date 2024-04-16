#include <cmath>
#include <iostream>

using namespace std;
using tp = int32_t;
constexpr tp Hat_Q = 500005;

template <typename Typex, unsigned _TSize>
struct WBLT {
  WBLT(const Typex& Val) : cnt(0), f(0) {
    _Size = new unsigned[_TSize];
    _Ln = new unsigned[_TSize];
    _Rn = new unsigned[_TSize];
    _Key = new Typex[_TSize];
    newnode(root, Val);
  }

  void newnode(const Typex& v) { newnode(root, v); }
  void insert(const Typex& x) { insert(root, x); }
  void erase(const unsigned& x) { erase(root, x); }
  Typex find(const unsigned& x) { return find(root, x); }
  unsigned rank(const Typex& x) { return rank(root, x); }

 protected:
  unsigned cnt, f, root, *_Size, *_Ln, *_Rn;
  Typex* _Key;

  void newnode(unsigned& cur, const Typex& val) {
    cur = ++cnt;
    _Size[cur] = 1;
    _Key[cur] = val;
  }

  void merge(const unsigned& l, const unsigned& r) {
    _Size[++cnt] = _Size[l] + _Size[r];
    _Key[cnt] = _Key[r];
    _Ln[cnt] = l;
    _Rn[cnt] = r;
  }

  void rotate(const unsigned& cur, const bool& r = false) {
    if (r) {
      merge(_Ln[cur], _Ln[_Rn[cur]]);
      _Ln[cur] = cnt;
      _Rn[cur] = _Rn[_Rn[cur]];
    } else {
      merge(_Rn[_Ln[cur]], _Rn[cur]);
      _Rn[cur] = cnt;
      _Ln[cur] = _Ln[_Ln[cur]];
    }
  }

  void maintain(const unsigned& cur) {
    if (_Size[_Ln[cur]] > _Size[_Rn[cur]] << 2)
      rotate(cur);
    else if (_Size[_Rn[cur]] > _Size[_Ln[cur]] << 2)
      rotate(cur, true);
    if (_Size[_Ln[cur]] > _Size[_Rn[cur]] << 2) {
      rotate(_Ln[cur], true);
      rotate(cur);
    } else if (_Size[_Rn[cur]] > _Size[_Ln[cur]] << 2) {
      rotate(_Rn[cur]);
      rotate(cur, true);
    }
  }

  void pushup(const unsigned& cur) {
    if (!_Size[_Ln[cur]])
      return;
    _Size[cur] = _Size[_Ln[cur]] + _Size[_Rn[cur]];
    _Key[cur] = _Key[_Rn[cur]];
  }

  void insert(const unsigned& cur, const Typex& x) {
    if (_Size[cur] == 1) {
      newnode(_Ln[cur], x < _Key[cur] ? x : _Key[cur]);
      newnode(_Rn[cur], x < _Key[cur] ? _Key[cur] : x);
      pushup(cur);
      return;
    }
    maintain(cur);
    insert(_Key[_Ln[cur]] < x ? _Rn[cur] : _Ln[cur], x);
    pushup(cur);
  }

  void erase(unsigned cur, const Typex& x) {
    if (_Size[cur] == 1) {
      cur = _Ln[f] == cur ? _Rn[f] : _Ln[f];
      _Size[f] = _Size[cur];
      _Ln[f] = _Ln[cur];
      _Rn[f] = _Rn[cur];
      _Key[f] = _Key[cur];
      return;
    }
    maintain(cur);
    f = cur;
    erase(_Key[_Ln[cur]] < x ? _Rn[cur] : _Ln[cur], x);
    pushup(cur);
  }

  Typex find(const unsigned& cur, const unsigned& x) {
    if (_Size[cur] == x)
      return _Key[cur];
    maintain(cur);
    if (x > _Size[_Ln[cur]])
      return find(_Rn[cur], x - _Size[_Ln[cur]]);
    return find(_Ln[cur], x);
  }

  unsigned rank(const unsigned& cur, const Typex& x) {
    if (_Size[cur] == 1)
      return 1;
    maintain(cur);
    if (_Key[_Ln[cur]] < x)
      return rank(_Rn[cur], x) + _Size[_Ln[cur]];
    return rank(_Ln[cur], x);
  }
};

tp val[Hat_Q];

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  WBLT<tp, Hat_Q> t(0x7fffffff);
  tp m, p, cnt = 0, size = 0;
  cin >> m >> p;
  while (m--) {
    string op;
    cin >> op;
    if (op == "push") {
      cin >> val[++cnt];
      t.insert(val[cnt]);
      ++size;
    } else if (op == "delete") {
      tp x;
      cin >> x;
      t.erase(val[x]);
      --size;
    } else {
      cout << t.find((size * p + 99) / 100) << '\n';
    }
  }
  return 0;
}
