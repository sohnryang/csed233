#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insertion(int key) {
  auto parent = _root;
  auto node = new Node(key);
  node->key = key;
  if (parent == nullptr) {
    _root = node;
    return 0;
  }
  while (true) {
    if (key < parent->key) {
      if (parent->left == nullptr) {
        parent->left = node;
        break;
      }
      parent = parent->left;
    } else if (key > parent->key) {
      if (parent->right == nullptr) {
        parent->right = node;
        break;
      }
      parent = parent->right;
    } else
      return -1;
  }
  return 0;
}

int BinarySearchTree::deletion(int key) {
  Node *node = _root, *parent = nullptr, *new_node;
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
    if (node == nullptr)
      return -1;
  }
  if (node->left == nullptr && node->right == nullptr)
    new_node = nullptr;
  else if (node->left != nullptr && node->right != nullptr) {
    auto right_root = node->right;
    new_node = right_root;
    Node *new_node_parent = nullptr;
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
    _root = new_node;
  else if (left_child)
    parent->left = new_node;
  else
    parent->right = new_node;
  delete node;
  return 0;
}
