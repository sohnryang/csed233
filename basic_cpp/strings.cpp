#include <iostream>
#include <string>

int main() {
  std::string s = "to be";
  std::string t = "not " + s;
  std::string u = s + " or " + t;
  std::cout << "s: " << s << std::endl;
  std::cout << "t: " << t << std::endl;
  std::cout << "u: " << u << std::endl;
  std::cout << "s > t: " << (s > t) << std::endl;
  return 0;
}
