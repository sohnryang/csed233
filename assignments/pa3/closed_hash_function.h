#pragma once
#include <iostream>
#include <string>
using namespace std;

class ClosedHashFunction {

public:
    ClosedHashFunction(int n, int r) : key_size(n), index_size(r) { };

    int closedhashing(int key);

private:
    int key_size;
    int index_size;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

