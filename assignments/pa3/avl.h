#pragma once
#include "bst.h"

using namespace std;

class AVLTree: public BinarySearchTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    int insertion(int key);
    int deletion(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};