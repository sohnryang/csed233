#include <iostream>

int main() {
  double f[5];
  int m[10];
  f[4] = 2.5;
  m[2] = 4;
  std::cout << f[(size_t)m[2]] << std::endl;

  char c[] = {'c', 'a', 't'};
  char *p = c;
  char *q = &c[0];
  char *r = &c[1];
  std::cout << "pointer p: " << reinterpret_cast<void *>(p) << std::endl;
  std::cout << "pointer q: " << reinterpret_cast<void *>(q) << std::endl;
  std::cout << "deref p: " << *p << std::endl;
  std::cout << "deref q: " << *q << std::endl;
  std::cout << "deref r-1: " << *(r - 1) << std::endl;
  std::cout << "deref r[-1]: " << r[-1] << std::endl;
  return 0;
}
