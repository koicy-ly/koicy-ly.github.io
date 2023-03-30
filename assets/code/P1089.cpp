#include <string>
#include <iostream>
#include <algorithm>

template <typename CO>
inline CO _(register const std::string & type, register CO & x) {
    if(type == "int" || type == "long" || type == "long long" || type == "short" || type == "signed") {
        register char ch = getchar();
        bool bol = false;
        if(ch == '-') {
            bol = true;
            ch = getchar();
        }
        for(x = 0; '0' <= ch && ch <= '9'; ch = getchar()) {
            x = x * 10 + ch - 48;
        }
        if(bol) {
            x = -x;
        }
        return x;
    }
    if(type == "unsigned int" || type == "unsigned long" || type == "unsigned long long" || type == "unsigned short") {
        register char ch = getchar();
        for(x = 0; '0' <= ch && ch <= '9'; ch = getchar()) {
            x = x * 10 + ch - 48;
        }
        return x;
    }
    if(type == "char" || type == "unsigned char") {
        return x = getchar();
    }
    if(type == "float" || type == "double" || type == "long double") {
        register char ch = getchar();
        bool bol = false;
        if(ch == '-') {
            bol = true;
            ch = getchar();
        }
        for(x = 0; '0' <= ch && ch <= '9'; ch = getchar()) {
            x = x * 10 + ch - 48;
        }
        if(ch == '.') {
            ch = getchar();
            for(register unsigned int cnt = 1; '0' <= ch && ch <= '9'; ch = getchar()) {
                cnt *= 10;
                x += (ch - 48) * 1.0 / cnt;
            }
        }
        if(bol) {
            x = -x;
        }
        return x;
    }
    if(type == "unsigned float" || type == "unsigned double" || type == "unsigned long double") {
        register char ch = getchar();
        for(x = 0; '0' <= ch && ch <= '9'; ch = getchar()) {
            x = x * 10 + ch - 48;
        }
        if(ch == '.') {
            ch = getchar();
            for(register unsigned int cnt = 1; '0' <= ch && ch <= '9'; ch = getchar()) {
                cnt *= 10;
                x += (ch - 48) * 1.0 / cnt;
            }
        }
        return x;
    }
    if(type == "bool && length = 1") {
        char B = getchar();
        return x = B != '0';
    }
    if(type == "bool && length = alpha") {
        register long long t;
        register char ch = getchar();
        for(t = 0; '0' <= ch && ch <= '9'; ch = getchar()) {
            t = t * 10 + ch - 48;
        }
        x = t;
        return x;
    }
    if(type == "cin") {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(0);
        std::cin >> x;
        return x;
    }
}

template <typename CO, typename ... COO>
inline void _(const std::string & type, CO & x, COO & ... y) {
    _(type, x);
    _(type, y ...);
}

int main() {
    const short h = 100, m = 300;
    short me, mom, month, plan[12];
    for (month = 0; month < 12; month++)
        scanf("%hd", &plan[month]);
    me = mom = 0;
    for (month = 0; month < 12; month++) {
        if ((me += m - plan[month]) < 0) {
            printf("-%d
", month + 1);
            return 0;
        }
        mom += me / h * h;
        me %= h;
    }
    me += mom * 6 / 5;
    printf("%d
", me);
    return 0;
}