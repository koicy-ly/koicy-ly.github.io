// Please submit with C++14! It's best to use C++20 or higher version.
constexpr bool __MTCS__ = 0;  // Spectre (v@rbtr.ee)
#ifndef LOCAL                 // By rbtree (https://rbtr.ee)
#pragma region HEAD           // DO OR DIE
#endif
#if OPTIMIZE
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
#define ra (__QWQ_IO__::__Read_I(), la)
#define rc __QWQ_IO__::__Read_C()
#define rgc __QWQ_IO__::getchar()
#define rs __QWQ_IO__::__Read_S()
#define fls __QWQ_IO__::flush()
#define wq __QWQ_IO__::qaq,
#define se(exp) begin(exp), end(exp)
#define LIKELY(exp) __builtin_expect(bool(exp), 1)
#define UNLIKELY(exp) __builtin_expect(bool(exp), 0)
#define qmx(exp1, exp2, exp3) exp1 = exp3(exp1, exp2)

typedef long long tp;
using namespace std;
void __Cored__(tp);
tp la;

namespace __QWQ_IO__ {
constexpr tp Size = 0x217217;
char in[Size], out[Size], stk[45];
char *s = in, *t = in, *S = out, *T = out + Size;
std::size_t top;
char getchar() {
#ifdef FREAD
  if (s == t)
    if (in == (t = (s = in) + fread(in, 1, Size, stdin))) return 10;
  return *s++;
#else
  return ::getchar();
#endif
}
void __Read_I() {
  bool f = 0;
  char c = getchar();
  for (; c < '0' || c > '9'; c = getchar()) f = c == '-';
  la = c & 15;
  for (c = getchar(); c > 47 && c < 58; c = getchar()) la = la * 10 + (c & 15);
  la = f ? -la : la;
}
char __Read_C() {
  char c = getchar();
  while (c == 10 || c == 32) c = getchar();
  return c;
}
string __Read_S() {
  string s;
  for (char c = __Read_C(); c != 32 && c != 10 && c != 13; c = getchar())
    s.push_back(c);
  return s;
}
void flush() { return fwrite(out, 1, S - out, stdout), S = out, void(); }
void __Write(char c) {
  *S++ = c;
  if (S == T) flush();
}
void __Write(string s) {
  for (std::size_t i = 0; i < s.size(); ++i) __Write(s[i]);
}
void __Write(const char *s) {
  while (*s) __Write(*s++);
}
template <typename _Type>
void __Write(_Type x) {
  if (!x) return __Write('0');
  if (x < 0) __Write('-');
  for (x = x < 0 ? ~x + 1 : x; x; x /= 10) stk[++top] = x % 10;
  while (top) __Write(char(stk[top--] | 48));
}
template <typename _Type, typename... Other>
void __Write(_Type x, Other... y) {
  return __Write(x), __Write(y...);
}
struct QAQ {
  template <typename _Type>
  QAQ &operator,(_Type x) {
    return __Write(x), *this;
  }
} qaq;
}  // namespace __QWQ_IO__

signed main(/* >_< */) {
  static tp __TCS__ = __MTCS__ ? ra : 1, __NOW__ = 0;
  while (__NOW__ < __TCS__) __Cored__(++__NOW__);
  if (__QWQ_IO__::S == __QWQ_IO__::out) return 0;
  fwrite(__QWQ_IO__::out, 1, __QWQ_IO__::S - __QWQ_IO__::out, stdout);
  if (*--__QWQ_IO__::S != 10) putchar(10);
  return 0;
}

#ifndef LOCAL
#pragma endregion HEAD
#endif
#define FREAD 0;
#define OPTIMIZE 0;

////////////////////////////////////////////////////////////////////////////////

constexpr tp Hat_N = 1e5 + 3;

vector<tp> e[Hat_N];

tp a[Hat_N], hson[Hat_N], dep[Hat_N], fa[Hat_N], ts[Hat_N], id[Hat_N],
   real[Hat_N], top[Hat_N], sum[Hat_N << 2], delay[Hat_N << 2];

tp n, p;

tp mad(tp x, tp y) { return x + y >= p ? x + y - p : x + y; }

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
  if (l == r) {
    sum[x] = a[real[l]];
    return;
  }
  build(x << 1, l, l + r >> 1);
  build(x << 1 | 1, l + r + 2 >> 1, r);
  sum[x] = mad(sum[x << 1], sum[x << 1 | 1]);
}

void pushdown(tp x, tp l, tp r) {
  tp mid = l + r >> 1;
  delay[x << 1] = mad(delay[x << 1], delay[x]);
  delay[x << 1 | 1] = mad(delay[x << 1 | 1], delay[x]);
  sum[x << 1] = mad(sum[x << 1], delay[x] * (mid - l + 1));
  sum[x << 1 | 1] = mad(sum[x << 1 | 1], delay[x] * (r - mid));
  delay[x] = 0;
}

void modify(tp x, tp l, tp r, tp ml, tp mr, tp d) {
  if (l >= ml && r <= mr) {
    sum[x] = mad(sum[x], (r - l + 1) * d);
    delay[x] = mad(delay[x], d);
  } else {
    tp mid = l + r >> 1;
    pushdown(x, l, r);
    if (mid >= ml) modify(x << 1, l, mid, ml, mr, d);
    if (mid < mr) modify(x << 1 | 1, mid + 1, r, ml, mr, d);
    sum[x] = mad(sum[x << 1], sum[x << 1 | 1]);
  }
}

tp query(tp x, tp l, tp r, tp ml, tp mr) {
  if (l >= ml && r <= mr) {
    return sum[x];
  } else {
    tp mid = l + r >> 1, sum = 0;
    pushdown(x, l, r);
    if (mid >= ml) sum = query(x << 1, l, mid, ml, mr);
    if (mid < mr) sum += query(x << 1 | 1, mid + 1, r, ml, mr);
    return sum % p;
  }
}

void op1(tp x, tp y, tp d) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    modify(1, 1, n, id[top[x]], id[x], d);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  modify(1, 1, n, id[x], id[y], d);
}

tp op2(tp x, tp y) {
  tp acc = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    acc = mad(acc, query(1, 1, n, id[top[x]], id[x]));
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  return mad(acc, query(1, 1, n, id[x], id[y]));
}

void op3(tp x, tp d) { modify(1, 1, n, id[x], id[x] + ts[x] - 1, d); }

tp op4(tp x) { return query(1, 1, n, id[x], id[x] + ts[x] - 1); }

void __Cored__([[maybe_unused]] tp __TID__) {
  tp m, r;
  n = ra;
  m = ra;
  r = ra;
  p = ra;
  for (tp i = 1; i <= n; ++i) a[i] = ra % p;
  for (tp i = 1; i < n; ++i) {
    tp u = ra, v = ra;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  sub(r, r);
  tag(r, r);
  build(1, 1, n);
  while (m--) {
    if (tp op = ra; op == 1) {
      tp x = ra, y = ra, z = ra;
      op1(x, y, z);
    } else if (op == 2) {
      tp x = ra, y = ra;
      wq op2(x, y), '\n';
    } else if (op == 3) {
      tp x = ra, y = ra;
      op3(x, y);
    } else wq op4(ra), '\n';
  }
}

//*/