#pragma once

#include <cstddef>

#include <bitmask.h> //expand: true

template <typename T> void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T> class PriorityQueue {
private:
  T *internal_arr;
  size_t height, node_count, capacity;
  void normalize_subtree(size_t root);

public:
  PriorityQueue<T>(size_t height);
  PriorityQueue<T>();
  PriorityQueue<T>(const T *arr, size_t node_count);
  ~PriorityQueue<T>();
  T *get_internal_array() const;
  bool empty() const;
  size_t size() const;
  void insert(T element);
  T remove();
};

template <typename T> void PriorityQueue<T>::normalize_subtree(size_t root) {
  size_t current_index = root;
  while (true) {
    size_t left_child_index = 2 * current_index,
           right_child_index = 2 * current_index + 1;
    if (left_child_index > node_count && right_child_index > node_count)
      break;
    size_t new_index = current_index;
    if (left_child_index <= node_count &&
        internal_arr[left_child_index] < internal_arr[new_index])
      new_index = left_child_index;
    if (right_child_index <= node_count &&
        internal_arr[right_child_index] < internal_arr[new_index])
      new_index = right_child_index;
    if (new_index == current_index)
      break;
    swap(internal_arr[current_index], internal_arr[new_index]);
    current_index = new_index;
  }
}

template <typename T>
PriorityQueue<T>::PriorityQueue(size_t height)
    : height(height), node_count(0), capacity(1 << height) {
  internal_arr = new T[capacity];
}

template <typename T> PriorityQueue<T>::PriorityQueue() : PriorityQueue<T>(1) {}

template <typename T>
PriorityQueue<T>::PriorityQueue(const T *arr, size_t node_count)
    : node_count(node_count) {
  if (node_count == 0) {
    height = 1;
    capacity = 1 << height;
    internal_arr = new T[capacity];
    return;
  }
  height = log2_floor<size_t>(node_count) + 1;
  capacity = 1 << height;
  internal_arr = new T[capacity];
  for (size_t i = 1; i <= node_count; i++)
    internal_arr[i] = arr[i - 1];
  for (size_t k = node_count / 2; k >= 1; k--)
    normalize_subtree(k);
}

template <typename T> PriorityQueue<T>::~PriorityQueue() {
  delete[] internal_arr;
}

template <typename T> T *PriorityQueue<T>::get_internal_array() const {
  return internal_arr;
}

template <typename T> bool PriorityQueue<T>::empty() const {
  return node_count == 0;
}

template <typename T> size_t PriorityQueue<T>::size() const {
  return node_count;
}

template <typename T> void PriorityQueue<T>::insert(T element) {
  if (capacity == node_count + 1) {
    capacity *= 2;
    T *new_arr = new T[capacity];
    for (int i = 1; i <= node_count; i++)
      new_arr[i] = internal_arr[i];
    delete[] internal_arr;
    internal_arr = new_arr;
  }
  internal_arr[node_count + 1] = element;
  size_t current_index = ++node_count;
  while (current_index != 1) {
    size_t parent_index = current_index / 2;
    if (internal_arr[current_index] >= internal_arr[parent_index])
      break;
    swap(internal_arr[current_index], internal_arr[parent_index]);
    current_index = parent_index;
  }
}

template <typename T> T PriorityQueue<T>::remove() {
  T min_element = internal_arr[1];
  internal_arr[1] = internal_arr[node_count--];
  normalize_subtree(1);
  return min_element;
}
