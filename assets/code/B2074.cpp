#include <iostream>

using namespace std;

int main() {
    int a, b, dy;
    cin >> a >> b;
    dy = a;
    for (int i = 1; i < b; i++)
        dy = dy * a % 7;
    switch (dy) {
        case 0: printf("Sun"); break;
        case 1: printf("Mon"); break;
        case 2: printf("Tues"); break;
        case 3: printf("Wednes"); break;
        case 4: printf("Thurs"); break;
        case 5: printf("Fri"); break;
        default: printf("Satur");
    }
    cout << "day";
    return 0;
}