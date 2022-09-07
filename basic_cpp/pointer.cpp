#include <iostream>

int main() {
  char ch = 'Q';
  char *p = &ch;
  std::cout << "address: " << reinterpret_cast<void *>(p) << std::endl;
  std::cout << "refernced value: " << *p << std::endl;
  ch = 'Z';
  std::cout << "refernced value: " << *p << std::endl;
  *p = 'X';
  std::cout << "refernced value: " << *p << std::endl;
  return 0;
}
