#include <iostream>

enum MealType { NO_PREF, REGULAR, LOW_FAT, VEGETARIAN };

struct Passenger {
  std::string name;
  MealType meal;
  bool frequent;
  std::string frequent_flyer_num;
};

int main() {
  Passenger *p = new Passenger();
  p->name = "Alice";
  p->meal = REGULAR;
  p->frequent = false;
  p->frequent_flyer_num = "";
  std::cout << "addr: " << reinterpret_cast<void *>(p) << std::endl;
  std::cout << "name: " << p->name << std::endl;
  delete p;
  std::cout << "addr (after dealloc): " << reinterpret_cast<void *>(p)
            << std::endl;

  char *buf = new char[500];
  std::cout << "addr of buf: " << reinterpret_cast<void *>(buf) << std::endl;
  buf[0] = 'a';
  std::cout << "buf[0]: " << buf[0] << std::endl;
  delete[] buf;
  return 0;
}
