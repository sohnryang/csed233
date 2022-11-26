#pragma once

#include <deque.h> // expand: true
#include <utils.h> // expand: true

template <typename K, typename V> struct AVLNode {
  K key;
  V value;
  AVLNode<K, V> *left, *right;
  int height;

  int balancing_factor();
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
  void lr_rotate(AVLNode<K, V> *node);
  void rl_rotate(AVLNode<K, V> *node);
  void insert(K key, V value);
  void remove(K key);
};

template <typename K, typename V> int AVLNode<K, V>::balancing_factor() {
  int left_height = -1;
  if (left != nullptr)
    left_height = left->height;
  int right_height = -1;
  if (right != nullptr)
    right_height = right->height;
  return left_height - right_height;
}

template <typename K, typename V> AVLTree<K, V>::AVLTree() : root(nullptr) {}

template <typename K, typename V> int safe_height(AVLNode<K, V> *node) {
  if (node == nullptr)
    return -1;
  return node->height;
}

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
  int left_left_height = safe_height(left_left_child),
      left_right_height = safe_height(left_right_child),
      right_height = safe_height(right_child);
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
  int left_height = safe_height(left_child),
      right_left_height = safe_height(right_left_child),
      right_right_height = safe_height(right_right_child);
  node->left->height = 1 + max(left_height, right_left_height);
  node->height = 1 + max(node->left->height, right_right_height);
}

template <typename K, typename V>
void AVLTree<K, V>::lr_rotate(AVLNode<K, V> *node) {
  rr_rotate(node->left);
  ll_rotate(node);
}

template <typename K, typename V>
void AVLTree<K, V>::rl_rotate(AVLNode<K, V> *node) {
  ll_rotate(node->right);
  rr_rotate(node);
}

template <typename K, typename V> void AVLTree<K, V>::insert(K key, V value) {
  auto parent = root;
  auto node = new AVLNode<K, V>();
  node->key = key;
  node->value = value;
  if (parent == nullptr) {
    root = node;
    return;
  }
  Deque<AVLNode<K, V> *> parents;
  Deque<bool> left_child;
  while (true) {
    parents.push_back(parent);
    if (key < parent->key) {
      left_child.push_back(true);
      if (parent->left == nullptr) {
        parent->left = node;
        break;
      }
      parent = parent->left;
    } else if (key > parent->key) {
      left_child.push_back(false);
      if (parent->right == nullptr) {
        parent->right = node;
        break;
      }
      parent = parent->right;
    }
  }
  AVLNode<K, V> *current_node;
  int child_bf = 0;
  while (!parents.empty()) {
    current_node = parents.pop_back();
    bool is_left = left_child.pop_back();
    int left_height = safe_height(current_node->left),
        right_height = safe_height(current_node->right);
    current_node->height = 1 + max(left_height, right_height);
    if (abs(current_node->balancing_factor()) > 1) {
      if (is_left) {
        if (child_bf >= 0)
          ll_rotate(current_node);
        else
          lr_rotate(current_node);
      } else {
        if (child_bf <= 0)
          rr_rotate(current_node);
        else
          rl_rotate(current_node);
      }
    }
    child_bf = current_node->balancing_factor();
  }
}
