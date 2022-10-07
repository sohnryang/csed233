#pragma once
#include <iostream>
#include <string>
using namespace std;

class MinHeap {

public:
    MinHeap();

    int heap_size;
    int *heap_arr;

    void minHeapProp(int);
    void insertKey(int);
    void deleteMin();
    void deleteElement(int);
    string printHeap();

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add Private members if required ///////////


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

};