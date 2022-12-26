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
  swap_val(node->key, node->left->key);
  swap_val(node->value, node->left->value);
  swap_val(node->left->left, node->right);
  swap_val(node->left->left, node->left->right);
  swap_val(node->left, node->right);
  int left_left_height = safe_height(left_left_child),
      left_right_height = safe_height(left_right_child),
      right_height = safe_height(right_child);
  node->right->height = 1 + max_val(left_right_height, right_height);
  node->height = 1 + max_val(node->right->height, left_left_height);
}

template <typename K, typename V>
void AVLTree<K, V>::rr_rotate(AVLNode<K, V> *node) {
  auto left_child = node->left, right_left_child = node->right->left,
       right_right_child = node->right->right;
  swap_val(node->key, node->right->key);
  swap_val(node->value, node->right->value);
  swap_val(node->right->right, node->left);
  swap_val(node->right->left, node->right->right);
  swap_val(node->left, node->right);
  int left_height = safe_height(left_child),
      right_left_height = safe_height(right_left_child),
      right_right_height = safe_height(right_right_child);
  node->left->height = 1 + max_val(left_height, right_left_height);
  node->height = 1 + max_val(node->left->height, right_right_height);
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
  Deque<bool> child_dir;
  while (true) {
    parents.push_back(parent);
    if (key < parent->key) {
      child_dir.push_back(true);
      if (parent->left == nullptr) {
        parent->left = node;
        break;
      }
      parent = parent->left;
    } else if (key > parent->key) {
      child_dir.push_back(false);
      if (parent->right == nullptr) {
        parent->right = node;
        break;
      }
      parent = parent->right;
    }
  }
  int child_bf = 0;
  while (!parents.empty()) {
    AVLNode<K, V> *current;
    current = parents.pop_back();
    bool is_left = child_dir.pop_back();
    int left_height = safe_height(current->left),
        right_height = safe_height(current->right);
    current->height = 1 + max_val(left_height, right_height);
    if (abs(current->balancing_factor()) > 1) {
      if (is_left) {
        if (child_bf >= 0)
          ll_rotate(current);
        else
          lr_rotate(current);
      } else {
        if (child_bf <= 0)
          rr_rotate(current);
        else
          rl_rotate(current);
      }
    }
    child_bf = current->balancing_factor();
  }
}

template <typename K, typename V> void AVLTree<K, V>::remove(K key) {
  AVLNode<K, V> *node = root, *parent = nullptr, *new_node;
  bool left_child;
  Deque<AVLNode<K, V> *> parents;
  Deque<bool> child_dir;
  while (node->key != key) {
    parent = node;
    parents.push_back(parent);
    if (key < node->key) {
      node = node->left;
      child_dir.push_back(true);
      left_child = true;
    } else {
      node = node->right;
      child_dir.push_back(false);
      left_child = false;
    }
  }
  if (node->left == nullptr && node->right == nullptr) {
    new_node = nullptr;
  } else if (node->left != nullptr && node->right != nullptr) {
    Deque<AVLNode<K, V> *> subtree_parents;
    Deque<bool> subtree_child_dir;
    subtree_child_dir.push_back(false);
    auto right_root = node->right;
    new_node = right_root;
    AVLNode<K, V> *new_node_parent = nullptr;
    while (new_node->left != nullptr) {
      subtree_parents.push_back(new_node);
      subtree_child_dir.push_back(true);
      new_node_parent = new_node;
      new_node = new_node->left;
    }
    subtree_parents.push_front(new_node);
    while (!subtree_parents.empty()) {
      parents.push_back(subtree_parents.pop_front());
      child_dir.push_back(subtree_child_dir.pop_front());
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
  int child_bf = 0;
  bool first = true;
  while (!parents.empty()) {
    AVLNode<K, V> *current;
    current = parents.pop_back();
    bool is_left = child_dir.pop_back();
    int left_height = safe_height(current->left),
        right_height = safe_height(current->right);
    current->height = 1 + max_val(left_height, right_height);
    if (abs(current->balancing_factor()) > 1) {
      if (first) {
        if (current->left != nullptr && current->right != nullptr)
          ll_rotate(current);
        else if (current->left == nullptr)
          rr_rotate(current);
        else
          ll_rotate(current);
        first = false;
      } else {
        if (is_left) {
          if (child_bf >= 0)
            ll_rotate(current);
          else
            lr_rotate(current);
        } else {
          if (child_bf <= 0)
            rr_rotate(current);
          else
            rl_rotate(current);
        }
      }
    }
    child_bf = current->balancing_factor();
  }
  delete node;
}
