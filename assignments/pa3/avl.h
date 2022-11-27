#pragma once
#include "bst.h"

using namespace std;

class AVLTree : public BinarySearchTree {
public:
  AVLTree(){};
  ~AVLTree(){};

  void ll_rotate(Node *node);
  void rr_rotate(Node *node);
  void lr_rotate(Node *node);
  void rl_rotate(Node *node);
  int insertion(int key);
  int deletion(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
