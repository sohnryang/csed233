#pragma once

#include <deque.h> // expand: true
#include <utils.h> // expand: true

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
  void ll_rotate(AVLNode<K, V> *node);
  void rr_rotate(AVLNode<K, V> *node);
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

template <typename K, typename V>
void AVLTree<K, V>::ll_rotate(AVLNode<K, V> *node) {
  auto right_child = node->right, left_left_child = node->left->left,
       left_right_child = node->left->right;
  swap(node->key, node->left->key);
  swap(node->value, node->left->value);
  swap(node->left->left, node->right);
  swap(node->left->left, node->left->right);
  swap(node->left, node->right);
  int left_left_height = -1;
  if (left_left_child != nullptr)
    left_left_height = left_left_child->height;
  int left_right_height = -1;
  if (left_right_child != nullptr)
    left_right_height = left_right_child->height;
  int right_height = -1;
  if (right_child != nullptr)
    right_height = right_child->height;
  node->right->height = 1 + max(left_right_height, right_height);
  node->height = 1 + max(node->right->height, left_left_height);
}

template <typename K, typename V>
void AVLTree<K, V>::rr_rotate(AVLNode<K, V> *node) {
  auto left_child = node->left, right_left_child = node->right->left,
       right_right_child = node->right->right;
  swap(node->key, node->right->key);
  swap(node->value, node->right->value);
  swap(node->right->right, node->left);
  swap(node->right->left, node->right->right);
  swap(node->left, node->right);
  int left_height = -1;
  if (left_child != nullptr)
    left_height = left_child->height;
  int right_left_height = -1;
  if (right_left_child != nullptr)
    right_left_height = right_left_child->height;
  int right_right_height = -1;
  if (right_right_child != nullptr)
    right_right_height = right_right_child->height;
  node->left->height = 1 + max(left_height, right_left_height);
  node->height = 1 + max(node->left->height, right_right_height);
}
