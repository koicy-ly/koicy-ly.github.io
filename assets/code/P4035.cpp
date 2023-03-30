/*
 * Please submit with C++14! It's best to use C++20 or higher version.
 * By rbtree (https://rbtr.ee)
 * Spectre (v@rbtr.ee)
 * DO OR DIE
 */

#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;
typedef long long tp;

constexpr tp Hat_N = 13;
tp n;

struct Point {
  double l[Hat_N];

  Point() = default;

  double& operator[](tp index) { return l[index]; }

  Point operator+(Point _l) {
    Point ret;
    for (tp i = 0; i < n; ++i) ret[i] = l[i] + _l[i];
    return ret;
  }

  Point operator-(Point _l) {
    Point ret;
    for (tp i = 0; i < n; ++i) ret[i] = l[i] - _l[i];
    return ret;
  }
} p[Hat_N];

double dis(Point l) {
  double ret = 0;
  for (tp i = 0; i < n; ++i) ret += l[i] * l[i];
  return sqrt(ret);
}

double err(Point O) {
  double ret = 0;
  for (tp i = 0; i <= n; ++i) ret += dis(O - p[i]);
  return ret;
}

Point SA(Point tar) {
  double tIm = 5000;
  Point delta;
  while (tIm > 1e-5) {
    double sum = err(tar) / (n + 1);
    for (tp i = 0; i < n; ++i) delta[i] = 0;
    for (tp i = 0; i < n; ++i) {
      for (tp j = 0; j <= n; ++j)
        delta[i] += (dis(tar - p[j]) - sum) * (p[j][i] - tar[i]);
    }
    for (tp i = 0; i < n; ++i) tar[i] += delta[i] * tIm / (n + 1);
    tIm *= 0.99995;
  }
  return tar;
}

signed main() {
  cin >> n;
  Point O;
  cout.flags(ios_base::fixed);
  for (tp i = 0; i <= n; ++i) {
    for (tp j = 0; j < n; ++j) {
      cin >> p[i][j];
      O[j] += p[i][j] / (n + 1);
    }
  }
  cout << setprecision(3);
  O = SA(O);
  for (tp i = 0; i < n; ++i) cout << O[i] << " 
"[i + 1 == n];
  return 0;
}

//*/
