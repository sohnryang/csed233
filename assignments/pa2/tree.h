#pragma once
#include <string>
#include <fstream>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder();
  string postOrder();
  string inOrder();
  string isProper();
  string isFull();
  string isComplete();
  string getDepthHeight(int node_value);
private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};