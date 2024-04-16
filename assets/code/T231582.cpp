#include <fstream>
#include <iostream>

namespace Fast_I {
char *_Buf, *_Start_ptr, *_End_ptr;
std::streambuf* inbuf;
unsigned int Size;
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
  template <typename Typex>
  void operator()(Typex& _Val) { *this >> _Val; }
  template <typename Typex, typename... More>
  void operator()(Typex&, More&...);
  std::streambuf* rdbuf() { return inbuf; }
  void rdbuf(std::streambuf* _inbuf) { inbuf = _inbuf; }
  void rdbuf(const char*);
  void pop();
  char peek();
};
}  // namespace Fast_I
namespace Fast_O {
std::string buf;
std::streambuf* outbuf;

struct Fast_Ostream {
  Fast_Ostream(std::streambuf*, unsigned int);
  Fast_Ostream(std::streambuf* out) { outbuf = out; }
  Fast_Ostream(const char*, unsigned int);
  Fast_Ostream(unsigned int);
  void flush();
  ~Fast_Ostream();
  void endl() { buf.push_back('\n'); }
  template <typename Typex>
  void endl(const Typex& _Val);
  template <typename Typex, typename... More>
  void endl(const Typex&, const More&...);
  template <typename Typex>
  void operator()(const Typex& _Val);
  template <typename Typex, typename... More>
  void operator()(const Typex&, const More&...);
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
Fast_I::Fast_Istream fin(std::cin.rdbuf(), 1048576);  // 1 MB
Fast_O::Fast_Ostream fout(std::cout.rdbuf());         // \u221e
}  // namespace Fast_IO

#define cin Fast_IO::fin
#define cout Fast_IO::fout

/* ------------------------------------- */

signed main() {
  for (int64_t i = 0; i < 40000000; ++i) {
    int64_t x;
    cin >> x;
    cout << x << ' ';
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
}
Fast_Istream::Fast_Istream(const char* in, unsigned int Sz) {
  _Ok = 1;
  Fast_I::Size = Sz;
  rdbuf(in);
  _Start_ptr = _End_ptr = _Buf = new char[Sz];
}
Fast_Istream::Fast_Istream(unsigned int Sz) {
  _Ok = 1;
  Fast_I::Size = Sz;
  _Start_ptr = _End_ptr = _Buf = new char[Sz];
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
    bool _F = 0;
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
    bool _F = 0;
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
template <typename Typex, typename... More>
void Fast_Istream::operator()(Typex& _Val, More&... _More) {
  *this >> _Val;
  operator()(_More...);
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
  buf.reserve(Size);
  outbuf = out;
}
Fast_Ostream::Fast_Ostream(const char* File, unsigned int Size) {
  buf.reserve(Size);
  rdbuf(File);
}
void Fast_Ostream::rdbuf(const char* File) {
  static std::ofstream __Out__(File);
  rdbuf(__Out__.rdbuf());
}
Fast_Ostream::Fast_Ostream(unsigned int Size) {
  buf.reserve(Size);
}
void Fast_Ostream::flush() {
  outbuf->sputn(buf.data(), buf.size());
  buf.clear();
}
Fast_Ostream::~Fast_Ostream() {
  flush();
}
Fast_Ostream& Fast_Ostream::operator<<(char _Val) {
  buf.push_back(_Val);
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(const char* _Val) {
  while (*_Val) {
    buf.push_back(*_Val++);
  }
  return *this;
}
Fast_Ostream& Fast_Ostream::operator<<(const std::string& _Val) {
  for (auto&& i : _Val) {
    buf.push_back(i);
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
    buf.push_back('0');
  }
  while (S_top) {
    buf.push_back(_Stack[S_top--]);
  }
  free(_Stack);
}
void Put_Int(long long _Val) {
  if (_Val < 0) {
    buf.push_back('-');
    Put_Unsigned(~_Val + 1);
  } else {
    Put_Unsigned(_Val);
  }
}
Fast_Ostream& Fast_Ostream::operator<<(bool _Val) {
  buf.push_back(_Val ? '1' : '0');
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
template <typename Typex>
void Fast_Ostream::endl(const Typex& _Val) {
  *this << _Val << '\n';
}
template <typename Typex, typename... More>
void Fast_Ostream::endl(const Typex& _Val, const More&... _More) {
  *this << _Val;
  endl(_More...);
}
template <typename Typex>
void Fast_Ostream::operator()(const Typex& _Val) {
  *this << _Val;
}
template <typename Typex, typename... More>
void Fast_Ostream::operator()(const Typex& _Val, const More&... _More) {
  *this << _Val;
  operator()(_More...);
}
}  // namespace Fast_O
