#pragma once
#include <iostream>
#include <string>
using namespace std;

class OpenHashFunction {

public:
  OpenHashFunction(int M) : index_size(M){};

  int openhashing(int key);

private:
  int index_size;
};
