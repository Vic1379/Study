class PrimeNumberGenerator {
 public:
  int a;
  explicit PrimeNumberGenerator(int start) {
    a = start;
  }
  int GetNextPrime() {
    if (a == 0 || a == 1) {
      a = 3;
      return 2;
    } else {
      bool f = true, t = true;
      int i;
      while (t) {
        i = 2;
        while (f && i <= sqrt(a)) {
          if (a % i == 0) f = false;
          else
            i++;
        }
        if (f == false) {
          a++;
          f = true;
        } else {
          a++;
          return a - 1;
        }
      }
    }
  }
};
