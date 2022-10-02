#include "double_linked_list.h"
#include <deque.h>

template <typename T> struct TreeNode {
  T data;
  TreeNode<T> *child, *sibling;
};

template <typename T> class KAryTree {
private:
  TreeNode<T> *root;

public:
  KAryTree();
  KAryTree(TreeNode<T> root);
  ~KAryTree();
  TreeNode<T> *root_node() const;
  void insert(TreeNode<T> *parent, TreeNode<T> *node);
  DoubleLinkedList<TreeNode<T> *> preorder();
};

template <typename T> KAryTree<T>::KAryTree() {
  this->root = new TreeNode<T>();
}

template <typename T> KAryTree<T>::KAryTree(TreeNode<T> root) {
  this->root = root;
}

template <typename T> KAryTree<T>::~KAryTree<T>() {
  Deque<TreeNode<T> *> stack;
  stack.push_back(this->root);
  while (!stack.empty()) {
    auto node = stack.pop_back();
    if (node == nullptr)
      continue;
    stack.push_back(node->sibling);
    stack.push_back(node->child);
    delete node;
  }
}

template <typename T> TreeNode<T> *KAryTree<T>::root_node() const {
  return this->root;
}

template <typename T>
void KAryTree<T>::insert(TreeNode<T> *parent, TreeNode<T> *node) {
  node->sibling = parent->child;
  parent->child = node;
}
