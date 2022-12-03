#include "closed_hash_table.h"
#include "closed_hash_function.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ClosedHashTable::ClosedHashTable(int table_size, ClosedHashFunction *hf)
    : table_size(table_size) {
  this->hf = hf;
  this->table = new int[this->table_size];
  this->states = new ClosedTableState[this->table_size];
  for (int i = 0; i < table_size; i++)
    this->states[i] = CLOSED_EMPTY;
}

ClosedHashTable::~ClosedHashTable() {
  delete[] this->table;
  delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void ClosedHashTable::print_table(ostream &out) {
  for (int i = 0; i < this->table_size; i++) {
    out << i << ": ";
    if (this->states[i] == CLOSED_EMPTY)
      out << "empty" << endl;
    else if (this->states[i] == CLOSED_DELETED)
      out << "deleted" << endl;
    else if (this->states[i] == CLOSED_OCCUPIED)
      out << this->table[i] << endl;
    else
      out << "unknown state" << endl;
  }
}

int ClosedHashTable::hash_probed(int key, int collision_count) {
  if (collision_count == 0)
    return hf->closedhashing(key) % table_size;
  return (hf->closedhashing(key) + collision_count * collision_count +
          collision_count + 1) %
         table_size;
}

void ClosedHashTable::insert(int key) {
  int collision_count = 0, hash_val;
  do {
    hash_val = hash_probed(key, collision_count++);
  } while (states[hash_val] != CLOSED_EMPTY);
  this->table[hash_val] = key;
  this->states[hash_val] = CLOSED_OCCUPIED;
}

void ClosedHashTable::erase(int key) {
  int collision_count = 0, hash_val;
  do {
    hash_val = hash_probed(key, collision_count++);
  } while (states[hash_val] != CLOSED_OCCUPIED || table[hash_val] != key);
  this->table[hash_val] = -1;
  this->states[hash_val] = CLOSED_DELETED;
}
