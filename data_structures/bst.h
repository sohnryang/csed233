#pragma once

#include <deque.h> // expand: true

template <typename K, typename V> struct BSTNode {
  K key;
  V value;
  BSTNode<K, V> *left, *right;
};

template <typename K, typename V> class BST {
private:
  BSTNode<K, V> *root;

public:
  BST();
  BST(BSTNode<K, V> *root);
  ~BST();
  BSTNode<K, V> *get_root() const;
  BSTNode<K, V> *get(K key) const;
  void insert(K key, V value);
  void remove(K key);
};

template <typename K, typename V> BST<K, V>::BST() : root(nullptr) {}

template <typename K, typename V>
BST<K, V>::BST(BSTNode<K, V> *root) : root(root) {}

template <typename K, typename V> BST<K, V>::~BST() {
  Deque<BSTNode<K, V> *> stack;
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

template <typename K, typename V> BSTNode<K, V> *BST<K, V>::get_root() const {
  return root;
}

template <typename K, typename V> BSTNode<K, V> *BST<K, V>::get(K key) const {
  auto current = root;
  while (current != nullptr && current->key != key) {
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return current;
}

template <typename K, typename V> void BST<K, V>::insert(K key, V value) {
  auto parent = root;
  auto node = new BSTNode<K, V>();
  node->key = key;
  node->value = value;
  if (parent == nullptr) {
    root = node;
    return;
  }
  while (true) {
    if (key < parent->key) {
      if (parent->left == nullptr) {
        parent->left = node;
        break;
      }
      parent = parent->left;
    }
    if (key > parent->key) {
      if (parent->right == nullptr) {
        parent->right = node;
        break;
      }
      parent = parent->right;
    }
  }
}

template <typename K, typename V> void BST<K, V>::remove(K key) {
  BSTNode<K, V> *node = root, *parent = nullptr, *new_node;
  bool left_child;
  while (node->key != key) {
    parent = node;
    if (key < node->key) {
      node = node->left;
      left_child = true;
    } else {
      node = node->right;
      left_child = false;
    }
  }
  if (node->left == nullptr && node->right == nullptr)
    new_node = nullptr;
  else if (node->left != nullptr && node->right != nullptr) {
    auto right_root = node->right;
    new_node = right_root;
    BSTNode<K, V> *new_node_parent = nullptr;
    while (new_node->left != nullptr) {
      new_node_parent = new_node;
      new_node = new_node->left;
    }
    if (new_node_parent != nullptr)
      new_node_parent->left = new_node->right;
    new_node->left = node->left;
    if (new_node != right_root)
      new_node->right = right_root;
  } else
    new_node = node->left != nullptr ? node->left : node->right;
  if (parent == nullptr)
    root = new_node;
  else if (left_child)
    parent->left = new_node;
  else
    parent->right = new_node;
  delete node;
}
