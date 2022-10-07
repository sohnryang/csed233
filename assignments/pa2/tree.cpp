#include "tree.h"
#include <cstring>
#include <iostream>
#include <string>

#include <deque.h> // expand: true

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::getDepthHeight(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "";

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string result;
  Deque<Node *> stack;
  stack.push_back(_root);
  while (!stack.empty()) {
    auto here = stack.pop_back();
    if (here == nullptr)
      continue;
    if (!result.empty())
      result += " ";
    result += here->value;
    stack.push_back(here->right);
    stack.push_back(here->left);
  }
  return result;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string result;
  Deque<Node *> stack;
  Deque<bool> visited;
  stack.push_back(_root);
  visited.push_back(false);
  while (!stack.empty()) {
    auto here = stack.pop_back();
    auto been_here = visited.pop_back();
    if (here == nullptr)
      continue;
    if (been_here) {
      if (!result.empty())
        result += " ";
      result += here->value;
      continue;
    }
    stack.push_back(here);
    visited.push_back(true);
    stack.push_back(here->right);
    visited.push_back(false);
    stack.push_back(here->left);
    visited.push_back(false);
  }
  return result;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string result;
  Deque<Node *> stack;
  Deque<bool> visited;
  stack.push_back(_root);
  visited.push_back(false);
  while (!stack.empty()) {
    auto here = stack.pop_back();
    auto been_here = visited.pop_back();
    if (here == nullptr)
      continue;
    if (been_here) {
      if (!result.empty())
        result += " ";
      result += here->value;
      continue;
    }
    stack.push_back(here->right);
    visited.push_back(false);
    stack.push_back(here);
    visited.push_back(true);
    stack.push_back(here->left);
    visited.push_back(false);
  }
  return result;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::isProper() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "False";

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::isFull() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "False";

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::isComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "False";

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
