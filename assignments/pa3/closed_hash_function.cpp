#include "closed_hash_function.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int ClosedHashFunction::closedhashing(int key) {
  int squared = key * key;
  auto offset = key_size - index_size / 2;
  return (squared & (((1 << index_size) - 1) << offset)) >> offset;
}
