#include <iostream>

using namespace std;

signed main() {
    long long a, b = 0;
    cin >> a;
    for (int i = 1; i <= a; ++i) {
        b += i;
        cout << b << '\n';
        
    }
}