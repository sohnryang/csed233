#include <iostream>
#include <string>

int main() {
  std::string author = "Sam";
  std::string &ref = author;
  author = "Bob";
  std::cout << "author: " << author << std::endl;
  return 0;
}
