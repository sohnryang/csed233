#pragma once

#include <deque.h> // expand: true

template <typename K, typename V> struct AVLNode {
  K key;
  V value;
  AVLNode<K, V> *left, *right;
  int height;
};

template <typename K, typename V> class AVLTree {
private:
  AVLNode<K, V> *root;

public:
  AVLTree<K, V>();
  AVLTree<K, V>(AVLNode<K, V> *root);
  ~AVLTree<K, V>();
  AVLNode<K, V> *get_root() const;
  AVLNode<K, V> *get(K key) const;
  void insert(K key, V value);
  void remove(K key);
};

template <typename K, typename V> AVLTree<K, V>::AVLTree() : root(nullptr) {}

template <typename K, typename V>
AVLTree<K, V>::AVLTree(AVLNode<K, V> *root) : root(root) {}

template <typename K, typename V> AVLTree<K, V>::~AVLTree<K, V>() {
  Deque<AVLNode<K, V> *> stack;
  stack.push_back(root);
  while (!stack.empty()) {
    auto here = stack.pop_back();
    if (here == nullptr)
      continue;
    stack.push_back(here->left);
    stack.push_back(here->right);
    delete here;
  }
}

template <typename K, typename V>
AVLNode<K, V> *AVLTree<K, V>::get_root() const {
  return this->root;
}

template <typename K, typename V>
AVLNode<K, V> *AVLTree<K, V>::get(K key) const {
  auto current = this->root;
  while (current != nullptr && current->key != key) {
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return current;
}
