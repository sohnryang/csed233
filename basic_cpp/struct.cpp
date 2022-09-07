#include <iostream>
#include <string>

enum MealType { NO_PREF, REGULAR, LOW_FAT, VEGETARIAN };

struct Passenger {
  std::string name;
  MealType meal;
  bool frequent;
  std::string frequent_flyer_num;
};

int main() {
  Passenger p = {"Bob", NO_PREF, true, "231242"};
  std::cout << "Name: " << p.name << std::endl;
  std::cout << "Meal: " << p.meal << std::endl;
  std::cout << "Frequent: " << p.frequent << std::endl;
  std::cout << "Frequent flyer number: " << p.frequent_flyer_num << std::endl;
  return 0;
}
