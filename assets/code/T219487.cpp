#include <iostream>
#include <string>
#include <bits/stdc++.h>

#define il inline
#define R register
#ifdef WIN64
#define L long
#else
#define L long long
#endif
#define RE exit(0);

using namespace std;

namespace IO {
    const int str = 1 << 20;
    static char in_buf[str], *in_s, *in_t;
    bool __ = false;
    il char gc() {
        return (in_s == in_t) && (in_t = (in_s = in_buf) + fread(in_buf, 1, str, stdin)), in_s == in_t ? EOF : *in_s++;
    }
    il void in(string &ch) {
        ch.clear();
        if(__)
            return;
        register char c;
        while((c = gc()) != EOF && isspace(c));
        if(c == EOF) {
            __ = true;
            return;
        }
        ch += c;
        while((c = gc()) != EOF && !isspace(c)) ch += c; if(c == EOF)
            __ = true;
    }
    il void in(char &ch) {
        if(__)
            return;
        R char c;
        while((c = gc()) != EOF && isspace(c));
        if(c == EOF)
            __ = true;
        else ch = c;
    }
    il void in(char *ch) {
        *ch='\0';
        if(__)
            return;
        R char c;
        while((c = gc()) != EOF && isspace(c));
        if(c == EOF) {
            __ = true;
            return;
        }
        *ch = c;
        ch++;
        while((c = gc()) != EOF && !isspace(c))
            *ch = c, ch++;
        if(c == EOF)
            __ = true;
        *ch = '\0';
    }
    template<typename T>
    il void in(T &x) {
        if(__)
            return;
        R char c = gc();
        bool f = false;
        while(c != EOF && (c < '0' || c > '9'))
            f ^= (c == '-'), c = gc();
        if(c == EOF) {
            __ = true;
            return;
        }
        x = 0;
        while(c != EOF && '0' <= c && c <= '9')
            x = x * 10 + c - 48, c = gc();
        if(c == EOF)
            __ = true;
        if(f)
            x = -x;
    }
    template<typename T,typename ... arr>
    il void in(T & x, arr & ... y) {
        in(x), in(y...);
    }
    const char ln = '\n';
    static char out_buf[str], *out_s = out_buf, *out_t = out_buf + str;
    il void flush() {
        fwrite(out_buf, 1, out_s - out_buf, stdout);
        out_s = out_buf;
    }
    il void pt(char c) {
        (out_s == out_t) ? (fwrite(out_s = out_buf, 1, str, stdout), *out_s ++ = c) : (*out_s ++ = c);
    }
    il void out(const char* s) {
        while(*s)
            pt(*s++);
    }
    il void out(char* s) {
        while(*s)
            pt(*s++);
    }
    il void out(char c) {
        pt(c);
    }
    il void out(string s) {
        for(R int i = 0; s[i]; i++)
            pt(s[i]);
    }
    template<typename T>
    il void out(T x) {
        if(!x) {
            pt('0');
            return;
        }
        if(x < 0)
            pt('-'), x = -x;
        char a[50], t = 0;
        while(x)
            a[t++] = x % 10, x /= 10;
        while(t--)
            pt(a[t] + '0');
    }
    template<typename T, typename ... arr>
    il void out(T x,arr & ... y) {
        out(x), out(y...);
    }
}
using namespace IO;

int x[10001];

int main() {
    int n;
    in(n);
    for(int i = 0; i < n; i++) {
        in(x[i]);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(x[j] == i + 1) {
                cout << ++j << " ";
                break;
            }
        }
    }
    RE
}