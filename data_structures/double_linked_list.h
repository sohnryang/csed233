#pragma once

template <typename T> struct TwoWayNode {
  T data;
  TwoWayNode *prev_ptr, *next_ptr;
};

template <typename T> class DoubleLinkedList {
private:
  TwoWayNode<T> *head, *tail;

public:
  DoubleLinkedList();
  ~DoubleLinkedList();
  int size() const;
  bool empty() const;
  TwoWayNode<T> *head_node() const;
  TwoWayNode<T> *tail_node() const;
  TwoWayNode<T> *get_index(int index) const;
  void insert(TwoWayNode<T> *place, TwoWayNode<T> *inserted);
  void push_front(TwoWayNode<T> *node);
  void push_back(TwoWayNode<T> *node);
  void remove(TwoWayNode<T> *node);
};

template <typename T> DoubleLinkedList<T>::DoubleLinkedList() {
  this->head = new TwoWayNode<T>();
  this->tail = new TwoWayNode<T>();
  this->head->next_ptr = this->tail;
  this->tail->prev_ptr = this->head;
}

template <typename T> DoubleLinkedList<T>::~DoubleLinkedList() {
  auto current = this->head_node();
  while (current) {
    auto next_node = current->next_ptr;
    delete current;
    current = next_node;
  }
}

template <typename T> int DoubleLinkedList<T>::size() const {
  int result = 0;
  auto current = this->head->next_ptr;
  while (current != this->tail) {
    result++;
    current = current->next_ptr;
  }
  return result;
}

template <typename T> bool DoubleLinkedList<T>::empty() const {
  return this->head->next_ptr == this->tail;
}

template <typename T> TwoWayNode<T> *DoubleLinkedList<T>::head_node() const {
  return this->head;
}
template <typename T> TwoWayNode<T> *DoubleLinkedList<T>::tail_node() const {
  return this->tail;
}

template <typename T>
TwoWayNode<T> *DoubleLinkedList<T>::get_index(int index) const {
  auto selected = this->head_node()->next_ptr;
  for (int i = 0; i < index; i++)
    selected = selected->next_ptr;
  return selected;
}

template <typename T>
void DoubleLinkedList<T>::insert(TwoWayNode<T> *place,
                                 TwoWayNode<T> *inserted) {
  auto before = place->prev_ptr, after = place;
  inserted->prev_ptr = before;
  inserted->next_ptr = after;
  before->next_ptr = inserted;
  after->prev_ptr = inserted;
}

template <typename T>
void DoubleLinkedList<T>::push_front(TwoWayNode<T> *node) {
  this->insert(this->head_node()->next_ptr, node);
}

template <typename T> void DoubleLinkedList<T>::push_back(TwoWayNode<T> *node) {
  this->insert(this->tail_node(), node);
}

template <typename T> void DoubleLinkedList<T>::remove(TwoWayNode<T> *node) {
  auto before = node->prev_ptr, after = node->next_ptr;
  before->next_ptr = after;
  after->prev_ptr = before;
}
