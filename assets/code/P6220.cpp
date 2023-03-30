#include <iostream>
#include <vector>

using namespace std;

const int N = 501;

bool b[N][N], in[N * N];
vector<int> e[N * N];
int n, m, t, f[N * N], _f[N * N], p[N * N], ma[N * N], ans;
char c;

int id(int x, int y) {
  return (x - 1) * m + y;
}

bool Dfs(int x) {
  if (f[x] == t) {
    return 0;
  }
  f[x] = t;
  for (int i : e[x]) {
    _f[i] = t;
    if (!p[i] || Dfs(p[i])) {
      return p[i] = x;
    }
  }
  return 0;
}

void M() {
  for (int i = 1; i <= id(n, m); ++i) {
    t = i;
    if (Dfs(i)) {
      ans++, ma[i] = 1;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> c;
      b[i][j] = c - '0';
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (!b[i][j]) {
        int x, y;
        for (int k = i; k >= 1; --k) {
          if (b[k][j]) {
            x = id(k, j);
            break;
          }
        }
        for (int k = j; k >= 1; --k) {
          if (b[i][k]) {
            y = id(i, k);
            break;
          }
        }
        e[x].push_back(y);
        in[x] = in[y] = 1;
      }
    }
  }
  M();
  cout << ans << '\n';
  t++;
  for (int i = 1; i <= id(n, m); ++i) {
    if (!ma[i]) {
      Dfs(i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int x = id(i, j);
      if (in[x] && f[x] != t) {
        cout << i << ' ' << j << ' ' << "DOLJE
";
      }
      if (in[x] && _f[x] == t) {
        cout << i << ' ' << j << ' ' << "DESNO
";
      }
    }
  }
  return 0;
}