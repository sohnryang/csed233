#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

MinHeap::MinHeap() {
  heap_size = 0;
  heap_arr = new int[100]; // Default array of size 100
}

string MinHeap::printHeap() {
  string answer;
  for (int i = 0; i < heap_size; i++)
    answer += to_string(heap_arr[i]) + " ";
  return answer;
}

void MinHeap::insertKey(int k) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  heap_arr[heap_size] = k;
  size_t current_index = heap_size++;
  while (current_index != 0) {
    size_t parent_index = (current_index + 1) / 2 - 1;
    if (heap_arr[current_index] >= heap_arr[parent_index])
      break;
    swap(heap_arr[current_index], heap_arr[parent_index]);
    current_index = parent_index;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::deleteMin() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  heap_arr[0] = heap_arr[--heap_size];
  minHeapProp(0);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::minHeapProp(int i) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int current_index = i;
  while (true) {
    int left_child_index = 2 * (current_index + 1) - 1,
        right_child_index = 2 * (current_index + 1);
    if (left_child_index >= heap_size && right_child_index >= heap_size)
      break;
    int new_index = current_index;
    if (left_child_index < heap_size &&
        heap_arr[left_child_index] < heap_arr[new_index])
      new_index = left_child_index;
    if (right_child_index < heap_size &&
        heap_arr[right_child_index] < heap_arr[new_index])
      new_index = right_child_index;
    if (new_index == current_index)
      break;
    swap(heap_arr[current_index], heap_arr[new_index]);
    current_index = new_index;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::deleteElement(int i) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  heap_arr[i] = heap_arr[--heap_size];
  minHeapProp(i);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
