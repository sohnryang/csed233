#pragma once
#include "closed_hash_function.h"
#include <iostream>
#include <string>
using namespace std;

enum ClosedTableState {
  CLOSED_EMPTY,
  CLOSED_OCCUPIED,
  CLOSED_DELETED,
};

class ClosedHashTable {
public:
  ClosedHashTable(int table_size, ClosedHashFunction *hf);
  ~ClosedHashTable();

  void print_table(ostream &out);

  int hash_probed(int key, int collision_count);
  void insert(int key);
  void erase(int key);

private:
  const int table_size;
  ClosedHashFunction *hf;
  int *table;
  ClosedTableState *states;
};
