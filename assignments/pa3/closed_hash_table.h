#pragma once
#include <iostream>
#include <string>
#include "closed_hash_function.h"
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

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

    void insert(int key);
    void erase(int key);

private:
    const int table_size;
    ClosedHashFunction *hf;
    int *table;
    ClosedTableState *states;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

