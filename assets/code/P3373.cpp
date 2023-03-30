#include <fstream>
#include <iostream>

namespace Fast_I {
char *_Buf, *_Start_ptr, *_End_ptr, *_Add;
std::streambuf* inbuf;
unsigned int Size, _Add_Top;
bool _Ok;

struct Fast_Istream {
  operator bool() { return _Ok; }
  Fast_Istream(std::streambuf*, unsigned int);
  Fast_Istream(unsigned int);
  Fast_Istream(const char*, unsigned int);
  Fast_Istream& operator>>(char&);
  Fast_Istream& operator>>(char*);
  Fast_Istream& operator>>(bool&);
  Fast_Istream& operator>>(short&);
  Fast_Istream& operator>>(int&);
  Fast_Istream& operator>>(long&);
  Fast_Istream& operator>>(long long&);
  Fast_Istream& operator>>(unsigned short&);
  Fast_Istream& operator>>(unsigned int&);
  Fast_Istream& operator>>(unsigned long&);
  Fast_Istream& operator>>(unsigned long long&);
  Fast_Istream& operator>>(float&);
  Fast_Istream& operator>>(double&);
  Fast_Istream& operator>>(long double&);
  Fast_Istream& operator>>(std::string&);
  std::streambuf* rdbuf() { return inbuf; }
  void rdbuf(std::streambuf* _inbuf) { inbuf = _inbuf; }
  void rdbuf(const char*);
  void pop();
  char peek();
};
}  // namespace Fast_I
namespace Fast_O {
char* buf;
unsigned int top;
std::streambuf* outbuf;

struct Fast_Ostream {
  Fast_Ostream(std::streambuf*, unsigned int);
  Fast_Ostream(const char*, unsigned int);
  Fast_Ostream(unsigned int);
  void flush();
  ~Fast_Ostream();
  template <typename Typex>
  void println(const Typex& _Val) {
    *this << _Val << '\n';
  }
  Fast_Ostream& operator<<(char);
  Fast_Ostream& operator<<(const char*);
  Fast_Ostream& operator<<(const std::string&);
  Fast_Ostream& operator<<(bool);
  Fast_Ostream& operator<<(short);
  Fast_Ostream& operator<<(int);
  Fast_Ostream& operator<<(long);
  Fast_Ostream& operator<<(long long);
  Fast_Ostream& operator<<(unsigned short);
  Fast_Ostream& operator<<(unsigned int);
  Fast_Ostream& operator<<(unsigned long);
  Fast_Ostream& operator<<(unsigned long long);
  std::streambuf* rdbuf() { return outbuf; }
  void rdbuf(std::streambuf* _outbuf) { outbuf = _outbuf; }
  void rdbuf(const char*);
};
}  // namespace Fast_O
namespace Fast_IO {
Fast_I::Fast_Istream fin(std::cin.rdbuf(), 1048576);    // 1 MB
Fast_O::Fast_Ostream fout(std::cout.rdbuf(), 8388608);  // 8 MB
}  // namespace Fast_IO

#define cin Fast_IO::fin
#define cout Fast_IO::fout

/* ------------------------------------- */

using namespace std;
using tp = long long;
constexpr tp Hat_S = 400003;

tp rec[Hat_S], delay_add[Hat_S], delay_mul[Hat_S];
tp p;

void build(tp x, tp l, tp r) {
  delay_add[x] = 0;
  delay_mul[x] = 1;
  if (l == r) {
    cin >> rec[x];
    rec[x] %= p;
    return;
  }
  tp mid = l + r >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  rec[x] = (rec[x << 1] + rec[x << 1 | 1]) % p;
}

void pushdown(tp x, tp l, tp r) {
  tp mid = l + r >> 1;
  rec[x << 1] = (rec[x << 1] * delay_mul[x] + delay_add[x] * (mid - l + 1)) % p;
  rec[x << 1 | 1] =
      (rec[x << 1 | 1] * delay_mul[x] + delay_add[x] * (r - mid)) % p;

  delay_mul[x << 1] = (delay_mul[x << 1] * delay_mul[x]) % p;
  delay_mul[x << 1 | 1] = (delay_mul[x << 1 | 1] * delay_mul[x]) % p;

  delay_add[x << 1] = (delay_add[x << 1] * delay_mul[x] + delay_add[x]) % p;
  delay_add[x << 1 | 1] =
      (delay_add[x << 1 | 1] * delay_mul[x] + delay_add[x]) % p;

  delay_add[x] = 0;
  delay_mul[x] = 1;
}

tp query(tp x, tp Lm, tp Rm, tp l, tp r) {
  if (r < Lm || Rm < l) {
    return 0;
  }
  if (l <= Lm && r >= Rm) {
    return rec[x];
  }
  pushdown(x, Lm, Rm);
  tp mid = Lm + Rm >> 1;
  return (query(x << 1, Lm, mid, l, r) + query(x << 1 | 1, mid + 1, Rm, l, r)) %
         p;
}

void update_add(tp x, tp Lm, tp Rm, tp l, tp r, tp k) {
  if (r < Lm || Rm < l) {
    return;
  }
  if (l <= Lm && r >= Rm) {
    rec[x] = (rec[x] + k * (Rm - Lm + 1)) % p;
    delay_add[x] = (delay_add[x] + k) % p;
    return;
  }
  pushdown(x, Lm, Rm);
  tp mid = Lm + Rm >> 1;
  update_add(x << 1, Lm, mid, l, r, k);
  update_add(x << 1 | 1, mid + 1, Rm, l, r, k);
  rec[x] = (rec[x << 1] + rec[x << 1 | 1]) % p;
}

void update_mul(tp x, tp Lm, tp Rm, tp l, tp r, tp k) {
  if (r < Lm || Rm < l) {
    return;
  }
  if (l <= Lm && r >= Rm) {
    rec[x] = (rec[x] * k) % p;
    delay_mul[x] = (delay_mul[x] * k) % p;
    delay_add[x] = (delay_add[x] * k) % p;
    return;
  }
  pushdown(x, Lm, Rm);
  tp mid = Lm + Rm >> 1;
  update_mul(x << 1, Lm, mid, l, r, k);
  update_mul(x << 1 | 1, mid + 1, Rm, l, r, k);
  rec[x] = (rec[x << 1] + rec[x << 1 | 1]) % p;
}

signed main() {
  tp n, m;
  cin >> n >> m >> p;
  build(1, 1, n);
  while (m--) {
    tp op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      tp k;
      cin >> k;
      update_mul(1, 1, n, l, r, k);
    } else if (op == 2) {
      tp k;
      cin >> k;
      update_add(1, 1, n, l, r, k);
    } else {
      cout.println(query(1, 1, n, l, r));
    }
  }
  return 0;
}

/* ------------------------------------- */

namespace Fast_I {
Fast_Istream::Fast_Istream(std::streambuf* in, unsigned int Sz) {
  _Ok = 1;
  Fast_I::Size = Sz;
  inbuf = in;
  _Start_ptr = _End_ptr = _Buf = new char[Sz];
  _Add = new char[256];
}
Fast_Istream::Fast_Istream(const char* in, unsigned int Sz) {
  _Ok = 1;
  Fast_I::Size = Sz;
  rdbuf(in);
  _Start_ptr = _End_ptr = _Buf = new char[Sz];
  _Add = new char[256];
}
Fast_Istream::Fast_Istream(unsigned int Sz) {
  _Ok = 1;
  Fast_I::Size = Sz;
  _Start_ptr = _End_ptr = _Buf = new char[Sz];
  _Add = new char[256];
}
void Fast_Istream::rdbuf(const char* File) {
  static std::ifstream __In__(File);
  rdbuf(__In__.rdbuf());
}
void Get_Char(char& _Val) {
  if (_Start_ptr == _End_ptr) {
    _Start_ptr = _Buf;
    _End_ptr = _Buf + inbuf->sgetn(_Buf, Size);
  }
  if (_Start_ptr == _End_ptr) {
    _Val = -1;
    _Ok = 0;
  } else {
    _Val = *_Start_ptr++;
  }
}
Fast_Istream& Fast_Istream::operator>>(char& _Val) {
  if (_Ok) {
    Get_Char(_Val);
    while (_Val == 32 || _Val == 10 || _Val == 13 || _Val == 8 || _Val == 9 ||
           _Val == 7 || _Val == 12 || _Val == 11) {
      Get_Char(_Val);
    }
  }
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(char* _Val) {
  if (_Ok) {
    Get_Char(*_Val);
    while (*_Val == 32 || *_Val == 10 || *_Val == 13 || *_Val == 8 ||
           *_Val == 9 || *_Val == 7 || *_Val == 12 || *_Val == 11) {
      Get_Char(*_Val);
    }
    while (*_Val != 32 && *_Val != 10 && *_Val && *_Val != -1 && *_Val != 9 &&
           *_Val != 11 && *_Val != 12) {
      Get_Char(*++_Val);
    }
    *_Val = 0;
    --_Start_ptr;
  }
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(std::string& _Val) {
  if (_Ok) {
    char c;
    Get_Char(c);
    while (c == 32 || c == 10 || c == 13 || c == 8 || c == 9 || c == 7 ||
           c == 12 || c == 11) {
      Get_Char(c);
    }
    for (_Val.clear();
         c != 32 && c != 10 && c && c != -1 && c != 9 && c != 11 && c != 12;
         Get_Char(c)) {
      _Val.push_back(c);
    }
    --_Start_ptr;
  }
  return *this;
}
template <typename Typex>
void Get_Int(Typex& _Val) {
  if (_Ok) {
    char ch;
    bool _F = false;
    for (Get_Char(ch); (ch < 48 || ch > 57) && ch != -1; Get_Char(ch)) {
      _F = ch == 45;
    }
    for (_Val = 0; ch > 47 && ch < 58 && ch != -1; Get_Char(ch)) {
      _Val = _Val * 10 + (ch ^ 48);
    }
    if (_F) {
      _Val = ~_Val + 1;
    }
    --_Start_ptr;
  }
}
template <typename Typex>
void Get_Unsigned(Typex& _Val) {
  if (_Ok) {
    char ch;
    Get_Char(ch);
    while ((ch < 48 || ch > 57) && ch != -1) {
      Get_Char(ch);
    }
    for (_Val = 0; ch > 47 && ch < 58 && ch != -1; Get_Char(ch)) {
      _Val = _Val * 10 + (ch ^ 48);
    }
    --_Start_ptr;
  }
}
template <typename Typex>
void Get_Double(Typex& _Val) {
  if (_Ok) {
    char ch;
    bool _F = false;
    for (Get_Char(ch); (ch < 48 || ch > 57) && ch != -1; Get_Char(ch)) {
      _F = ch == 45;
    }
    for (_Val = 0; ch > 47 && ch < 58 && ch != -1; Get_Char(ch)) {
      _Val = _Val * 10 + (ch ^ 48);
    }
    if (ch == 46) {
      unsigned long long _Pow = 1;
      for (Get_Char(ch); ch > 47 && ch < 58 && ch != -1; Get_Char(ch)) {
        _Val += Typex((ch ^ 48) * 1.0 / (_Pow *= 10));
      }
    }
    if (_F) {
      _Val = -_Val;
    }
    --_Start_ptr;
  }
}
Fast_Istream& Fast_Istream::operator>>(bool& _Val) {
  if (_Ok) {
    char ch;
    Get_Char(ch);
    while (ch == 32 || ch == 10 || ch == 13 || ch == 8 || ch == 9 || ch == 7 ||
           ch == 12 || ch == 11) {
      Get_Char(ch);
    }
    while (ch != 32 && ch != 10 && ch && ch != -1 && ch != 9 && ch != 11 &&
           ch != 12) {
      _Val |= ch != 48;
      Get_Char(ch);
    }
    --_Start_ptr;
  }
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(short& _Val) {
  Get_Int(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(int& _Val) {
  Get_Int(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(long& _Val) {
  Get_Int(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(long long& _Val) {
  Get_Int(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(unsigned short& _Val) {
  Get_Unsigned(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(unsigned int& _Val) {
  Get_Unsigned(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(unsigned long& _Val) {
  Get_Unsigned(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(unsigned long long& _Val) {
  Get_Unsigned(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(float& _Val) {
  Get_Double(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(double& _Val) {
  Get_Double(_Val);
  return *this;
}
Fast_Istream& Fast_Istream::operator>>(long double& _Val) {
  Get_Double(_Val);
  return *this;
}
void Fast_Istream::pop() {
  char ch;
  Get_Char(ch);
}
char Fast_Istream::peek() {
  if (_Start_ptr == _End_ptr) {
    _Start_ptr = _Buf;
    _End_ptr = _Buf + inbuf->sgetn(_Buf, Size);
  }
  if (_Start_ptr == _End_ptr) {
    _Ok = 0;
    return -1;
  } else {
    return *_Start_ptr;
  }
}
}  // namespace Fast_I
namespace Fast_O {
Fast_Ostream::Fast_Ostream(std::streambuf* out, unsigned int Size) {
  top = 0;
  buf = (char*)malloc(Size);
  outbuf = out;
}
Fast_Ostream::Fast_Ostream(const char* File, unsigned int Size) {
  top = 0;
  buf = (char*)malloc(Size);
  rdbuf(File);
}
void Fast_Ostream::rdbuf(const char* File) {
  static std::ofstream __Out__(File);
  rdbuf(__Out__.rdbuf());
}
Fast_Ostream::Fast_Ostream(unsigned int Size) {
  top = 0;
  buf = (char*)malloc(Size);
}
void Fast_Ostream::flush() {
  outbuf->sputn(buf, top);
  top = 0;
}
Fast_Ostream::~Fast_Ostream() {
  flush();
  free(buf);
}
Fast_Ostream& Fast_Ostream::operator<<(char _Val) {
  buf[top++] = _Val;
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(const char* _Val) {
  while (*_Val) {
    buf[top++] = *_Val++;
  }
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(const std::string& _Val) {
  for (auto&& i : _Val) {
    buf[top++] = i;
  }
  return *this;
}
template <typename Typex>
void Put_Unsigned(Typex _Val) {
  char* _Stack = (char*)malloc(sizeof(Typex) * 3);
  unsigned S_top = 0;
  while (_Val) {
    _Stack[++S_top] = (_Val % 10) ^ 48;
    _Val /= 10;
  }
  if (!S_top) {
    buf[top++] = 48;
  }
  while (S_top) {
    buf[top++] = _Stack[S_top--];
  }
  free(_Stack);
}
void Put_Int(long long _Val) {
  if (_Val < 0) {
    buf[top++] = '-';
    Put_Unsigned(~_Val + 1);
  } else {
    Put_Unsigned(_Val);
  }
}
Fast_Ostream& Fast_Ostream::operator<<(bool _Val) {
  buf[top++] = _Val ? '1' : '0';
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(short _Val) {
  Put_Int(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(int _Val) {
  Put_Int(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(long _Val) {
  Put_Int(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(long long _Val) {
  Put_Int(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(unsigned short _Val) {
  Put_Unsigned(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(unsigned int _Val) {
  Put_Unsigned(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(unsigned long _Val) {
  Put_Unsigned(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(unsigned long long _Val) {
  Put_Unsigned(_Val);
  return *this;
}
}  // namespace Fast_O