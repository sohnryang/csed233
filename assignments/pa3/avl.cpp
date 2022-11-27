#include "avl.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

#include <deque.h> // expand: true

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

void AVLTree::ll_rotate(Node *node) {
  auto right_child = node->right, left_left_child = node->left->left,
       left_right_child = node->left->right;
  swap(node->key, node->left->key);
  swap(node->left->left, node->right);
  swap(node->left->left, node->left->right);
  swap(node->left, node->right);
  int left_left_height = safe_height(left_left_child),
      left_right_height = safe_height(left_right_child),
      right_height = safe_height(right_child);
  node->right->height = 1 + max(left_right_height, right_height);
  node->height = 1 + max(node->right->height, left_left_height);
}

void AVLTree::rr_rotate(Node *node) {
  auto left_child = node->left, right_left_child = node->right->left,
       right_right_child = node->right->right;
  swap(node->key, node->right->key);
  swap(node->right->right, node->left);
  swap(node->right->left, node->right->right);
  swap(node->left, node->right);
  int left_height = safe_height(left_child),
      right_left_height = safe_height(right_left_child),
      right_right_height = safe_height(right_right_child);
  node->left->height = 1 + max(left_height, right_left_height);
  node->height = 1 + max(node->left->height, right_right_height);
}

void AVLTree::lr_rotate(Node *node) {
  rr_rotate(node->left);
  ll_rotate(node);
}

void AVLTree::rl_rotate(Node *node) {
  ll_rotate(node->right);
  rr_rotate(node);
}

int AVLTree::insertion(int key) {
  auto parent = _root;
  auto node = new Node(key);
  node->key = key;
  if (parent == nullptr) {
    _root = node;
    return 0;
  }
  Deque<Node *> parents;
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
    } else
      return -1;
  }
  int child_bf = 0;
  while (!parents.empty()) {
    Node *current;
    current = parents.pop_back();
    bool is_left = child_dir.pop_back();
    int left_height = safe_height(current->left),
        right_height = safe_height(current->right);
    current->height = 1 + max(left_height, right_height);
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
  return 0;
}

int AVLTree::deletion(int key) {
  Node *node = _root, *parent = nullptr, *new_node;
  bool left_child;
  Deque<Node *> parents;
  Deque<bool> child_dir;
  while (node->key != key) {
    parent = node;
    parents.push_back(parent);
    if (key < node->key) {
      node = node->left;
      child_dir.push_back(true);
      left_child = true;
    } else if (key > node->key) {
      node = node->right;
      child_dir.push_back(false);
      left_child = false;
    }
    if (node == nullptr)
      return -1;
  }
  if (node->left == nullptr && node->right == nullptr) {
    new_node = nullptr;
  } else if (node->left != nullptr && node->right != nullptr) {
    Deque<Node *> subtree_parents;
    Deque<bool> subtree_child_dir;
    subtree_child_dir.push_back(false);
    auto right_root = node->right;
    new_node = right_root;
    Node *new_node_parent = nullptr;
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
    _root = new_node;
  else if (left_child)
    parent->left = new_node;
  else
    parent->right = new_node;
  int child_bf = 0;
  bool first = true;
  while (!parents.empty()) {
    Node *current;
    current = parents.pop_back();
    bool is_left = child_dir.pop_back();
    int left_height = safe_height(current->left),
        right_height = safe_height(current->right);
    current->height = 1 + max(left_height, right_height);
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
  return 0;
}
