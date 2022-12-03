#include "open_hash_function.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int OpenHashFunction::openhashing(int key) {
  int folded = 0;
  while (key) {
    folded += key % 10;
    folded %= index_size;
    key /= 10;
  }
  return folded;
}
