#include "open_hash_table.h"
#include "open_hash_function.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

OpenHashTable::OpenHashTable(int table_size, OpenHashFunction *hf)
    : table_size(table_size) {
  this->hf = hf;
  table = new HashNode *[this->table_size];
  this->states = new OpenTableState[this->table_size];
  for (int i = 0; i < this->table_size; i++) {
    table[i] = NULL;
    states[i] = OPEN_EMPTY;
  }
}

OpenHashTable::~OpenHashTable() {
  for (int i = 0; i < table_size; i++) {
    auto current = table[i];
    while (current != nullptr) {
      auto next = current->next;
      delete current;
      current = next;
    }
  }
  delete[] table;
  delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void OpenHashTable::print_table(ostream &out) {
  for (int i = 0; i < this->table_size; i++) {
    out << i << ": ";
    if (this->states[i] == OPEN_EMPTY) {
      out << "empty" << endl;
    } else if (this->states[i] == OPEN_OCCUPIED) {
      HashNode *cur;
      cur = table[i];
      while (cur->next != NULL) {
        out << cur->key;
        out << ", ";
        cur = cur->next;
      }
      out << cur->key << endl;
    } else {
      out << "unknown state" << endl;
    }
  }
}

void OpenHashTable::insert(int key) {
  int hash_val = hf->openhashing(key);
  if (states[hash_val] == OPEN_EMPTY) {
    table[hash_val] = new HashNode(key);
    states[hash_val] = OPEN_OCCUPIED;
    return;
  }
  auto current = table[hash_val];
  while (current->next != nullptr)
    current = current->next;
  current->next = new HashNode(key);
}

void OpenHashTable::erase(int key) {
  int hash_val = hf->openhashing(key);
  HashNode *leader = nullptr, *current = table[hash_val];
  while (current->key != key) {
    leader = current;
    current = current->next;
  }
  if (leader == nullptr)
    table[hash_val] = current->next;
  else
    leader->next = current->next;
  delete current;
  if (table[hash_val] == nullptr)
    states[hash_val] = OPEN_EMPTY;
  return;
}
