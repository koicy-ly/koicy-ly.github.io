#include <iostream>

using namespace std;

int cnt = 0;
int a[1000];
bool x[1000], y[1000], z[1000];

inline void dfs(int row, int n) {
    if (row == n)
        if (cnt++ < 3) {
            for (int i = 0; i < n; i++)
                cout << a[i] + 1 << ' ';
            cout << '\n';
        }
    for (int i = 0; i < n; i++) {
        if (!x[i] && !y[i + row] && !z[i + n - row]) {
            a[row] = i;
            x[i] = y[i + row] = z[i + n - row] = true;
            dfs(row + 1, n);
            x[i] = y[i + row] = z[i + n - row] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    dfs(0, n);
    cout << cnt;
    return 0;
}