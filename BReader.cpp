#include <string>
#include <algorithm>

class BufferedReader {
 public:
  explicit BufferedReader(PackageStream* stream) : PS_(*stream) {}
  int32_t Read(char* buf, int32_t bytes) {
    int32_t bt = 0;
    int a, b, checking, ty = min(k, bytes);
    c = k;
    if (k != 0) {
      for (i = 0; i < ty; i++) {
        buf[i] = str[i + yt];
        k--;
      }
      if (ty == bytes) {
        if (k == 0) yt = 0;
        else
          yt += bytes;
        return bytes;
      } else {
        yt = 0;
        bytes -= c;
        bt += c;
      }
    }
    a = bytes / ln;
    for (i = 0; i < a; i++) {
      checking = PS_.ReadPackage(buf + (i * ln) + c);
      if (checking < ln) return bt + checking;
      bt += ln;
    }
    a = i * ln;
    b = bytes - a;
    if (b != 0) {
      unique_ptr<char[]> buftm2(new char[ln]);
      checking = PS_.ReadPackage(buftm2.get());
      int x = min(b, checking);
      memcpy(buf + a + c, buftm2.get(), x);
      k = checking - x;
      if (k != 0) str = string(buftm2.get() + x, buftm2.get() + checking);
      return bt + x;
    }
  }

 private:
  int i = 0, k = 0, c = 0, yt = 0;
  PackageStream PS_;
  string str;
  int ln = PS_.PackageLen();
};
