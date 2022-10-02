#pragma once

#include <double_linked_list.h>

template <typename T> class Deque {
private:
  int list_size;
  DoubleLinkedList<T> internal_list;

public:
  Deque();
  int size() const;
  bool empty() const;
  T pop_front();
  T pop_back();
  void push_front(T data);
  void push_back(T data);
};

template <typename T> Deque<T>::Deque() : list_size(0), internal_list() {}

template <typename T> int Deque<T>::size() const { return this->list_size; }

template <typename T> bool Deque<T>::empty() const {
  return this->internal_list.empty();
}

template <typename T> T Deque<T>::pop_front() {
  auto node = this->internal_list.head_node()->next_ptr;
  this->internal_list.remove(node);
  T data = node->data;
  delete node;
  this->list_size--;
  return data;
}

template <typename T> T Deque<T>::pop_back() {
  auto node = this->internal_list.tail_node()->prev_ptr;
  this->internal_list.remove(node);
  T data = node->data;
  delete node;
  this->list_size--;
  return data;
}

template <typename T> void Deque<T>::push_front(T data) {
  auto node = new TwoWayNode<T>();
  node->data = data;
  this->internal_list.push_front(node);
  this->list_size++;
}

template <typename T> void Deque<T>::push_back(T data) {
  auto node = new TwoWayNode<T>();
  node->data = data;
  this->internal_list.push_back(node);
  this->list_size++;
}
