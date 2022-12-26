#include <avl.h>
#include <bst.h>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <deque.h>
#include <double_linked_list.h>
#include <gtest/gtest.h>
#include <priority_queue.h>
#include <sorting.h>
#include <union_find.h>
#include <utility>
#include <utils.h>
#include <vector.h>

TEST(DoubleLinkedListTest, TestInit) {
  DoubleLinkedList<int> dl;
  EXPECT_EQ(dl.size(), 0);
  EXPECT_TRUE(dl.empty());
}

TEST(DoubleLinkedListTest, TestPush) {
  {
    DoubleLinkedList<int> dl;
    for (int i = 0; i < 5; i++) {
      auto node = new TwoWayNode<int>();
      node->data = i;
      dl.push_back(node);
    }
    EXPECT_EQ(dl.size(), 5);
    EXPECT_FALSE(dl.empty());
    for (int i = 0; i < 5; i++) {
      auto node = dl.get_index(i);
      EXPECT_EQ(node->data, i);
    }
  }

  {
    DoubleLinkedList<int> dl;
    for (int i = 0; i < 5; i++) {
      auto node = new TwoWayNode<int>();
      node->data = i;
      dl.push_front(node);
    }
    EXPECT_EQ(dl.size(), 5);
    EXPECT_FALSE(dl.empty());
    for (int i = 0; i < 5; i++) {
      auto node = dl.get_index(i);
      EXPECT_EQ(node->data, 4 - i);
    }
  }
}

TEST(DoubleLinkedListTest, TestIndex) {
  DoubleLinkedList<int> dl;
  TwoWayNode<int> *nodes[5];
  for (int i = 0; i < 5; i++) {
    auto node = new TwoWayNode<int>();
    nodes[i] = node;
    node->data = i;
    dl.push_back(node);
  }
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(nodes[i], dl.get_index(i));
}

TEST(DoubleLinkedListTest, TestRemove) {
  {
    DoubleLinkedList<int> dl;
    auto node = new TwoWayNode<int>();
    node->data = 1;
    dl.push_back(node);
    EXPECT_EQ(dl.size(), 1);
    dl.remove(node);
    EXPECT_TRUE(dl.empty());
    delete node;
  }

  {
    DoubleLinkedList<int> dl;
    for (int i = 0; i < 5; i++) {
      auto node = new TwoWayNode<int>();
      node->data = i;
      dl.push_back(node);
      dl.remove(node);
      delete node;
      EXPECT_EQ(dl.size(), 0);
      EXPECT_TRUE(dl.empty());
    }
  }
}

TEST(DoubleLinkedListTest, TestInsert) {
  DoubleLinkedList<int> dl;
  auto already_existed = TwoWayNode<int>{-1, nullptr, nullptr};
  for (int i = 0; i < 2; i++) {
    auto node = new TwoWayNode<int>(already_existed);
    dl.push_back(node);
  }
  auto node = new TwoWayNode<int>();
  dl.insert(dl.head_node()->next_ptr->next_ptr, node);
  auto inserted = dl.get_index(1);
  EXPECT_EQ(inserted, node);
}

TEST(DequeTest, TestInit) {
  Deque<int> dq;
  EXPECT_TRUE(dq.empty());
  EXPECT_EQ(dq.size(), 0);
}

TEST(DequeTest, TestPushPop) {
  Deque<int> dq;
  dq.push_back(1);
  EXPECT_FALSE(dq.empty());
  EXPECT_EQ(dq.size(), 1);
  int data = dq.pop_back();
  EXPECT_EQ(data, 1);
  EXPECT_TRUE(dq.empty());
  EXPECT_EQ(dq.size(), 0);

  dq.push_front(2);
  EXPECT_FALSE(dq.empty());
  EXPECT_EQ(dq.size(), 1);
  data = dq.pop_back();
  EXPECT_EQ(data, 2);
  EXPECT_TRUE(dq.empty());
  EXPECT_EQ(dq.size(), 0);

  for (int i = 0; i < 5; i++) {
    dq.push_back(i);
    EXPECT_EQ(dq.size(), i + 1);
  }
  for (int i = 0; i < 5; i++) {
    int data = dq.pop_front();
    EXPECT_EQ(data, i);
    EXPECT_EQ(dq.size(), 4 - data);
  }
}

TEST(DequeTest, TestGet) {
  Deque<int> dq;
  dq.push_back(1);
  EXPECT_EQ(dq.get_back(), 1);
  EXPECT_FALSE(dq.empty());
  EXPECT_EQ(dq.size(), 1);
  dq.push_front(2);
  EXPECT_EQ(dq.get_front(), 2);
  EXPECT_FALSE(dq.empty());
  EXPECT_EQ(dq.size(), 2);
  dq.pop_front();
  EXPECT_EQ(dq.get_front(), dq.get_back());
  EXPECT_EQ(dq.get_front(), 1);
  EXPECT_FALSE(dq.empty());
  EXPECT_EQ(dq.size(), 1);
}

TEST(BitmaskTest, TestLog2Floor) {
  EXPECT_EQ(log2_floor<int>(-1), -1);
  EXPECT_EQ(log2_floor<int>(0), -1);
  int values[] = {
      1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17,
  };
  for (auto v : values)
    EXPECT_EQ(log2_floor(v), (int)log2(v));
}

TEST(PriorityQueueTest, TestInit) {
  {
    PriorityQueue<int> pq;
    EXPECT_TRUE(pq.empty());
    EXPECT_EQ(pq.size(), 0);
  }
  {
    int arr[7] = {6, 5, 3, 2, 7, 1, 4};
    PriorityQueue<int> pq(arr, 7);
    EXPECT_EQ(pq.size(), 7);
    for (int i = 1; i <= 7; i++)
      EXPECT_EQ(pq.remove(), i);
    EXPECT_TRUE(pq.empty());
  }
  {
    int arr[7] = {0};
    PriorityQueue<int> pq(arr, 7);
    EXPECT_EQ(pq.size(), 7);
    for (int i = 1; i <= 7; i++)
      EXPECT_EQ(pq.remove(), 0);
    EXPECT_TRUE(pq.empty());
  }
}

TEST(PriorityQueueTest, TestInsert) {
  PriorityQueue<int> pq(2);
  pq.insert(2);
  pq.insert(1);
  pq.insert(3);
  auto arr = pq.get_internal_array();
  EXPECT_EQ(arr[1], 1);
  EXPECT_EQ(arr[2], 2);
  EXPECT_EQ(arr[3], 3);
  EXPECT_FALSE(pq.empty());
  EXPECT_EQ(pq.size(), 3);
}

TEST(PriorityQueueTest, TestRemove) {
  {
    PriorityQueue<int> pq(2);
    pq.insert(2);
    pq.insert(1);
    pq.insert(3);
    for (int i = 1; i <= 3; i++) {
      EXPECT_EQ(pq.remove(), i);
      EXPECT_EQ(pq.size(), 3 - i);
    }
    EXPECT_TRUE(pq.empty());
  }
  {
    PriorityQueue<int> pq(1);
    pq.insert(1);
    EXPECT_EQ(pq.remove(), 1);
    EXPECT_TRUE(pq.empty());
  }
  {
    PriorityQueue<int> pq(2);
    pq.insert(2);
    pq.insert(1);
    pq.insert(3);
    pq.insert(4);
    for (int i = 1; i <= 4; i++) {
      EXPECT_EQ(pq.remove(), i);
      EXPECT_EQ(pq.size(), 4 - i);
    }
    EXPECT_TRUE(pq.empty());
  }
}

TEST(BSTTest, TestGet) {
  {
    BST<int, int> tree;
    EXPECT_EQ(tree.get(0), nullptr);
  }
  {
    auto root = new BSTNode<int, int>();
    root->key = 3;
    root->value = 3;
    auto left_node = new BSTNode<int, int>();
    left_node->key = 2;
    left_node->value = 2;
    auto right_node = new BSTNode<int, int>();
    right_node->key = 4;
    right_node->value = 4;

    root->left = left_node;
    root->right = right_node;

    auto left_left_node = new BSTNode<int, int>();
    left_left_node->key = 1;
    left_left_node->value = 1;

    left_node->left = left_left_node;

    BST<int, int> tree(root);
    EXPECT_EQ(tree.get_root(), root);
    EXPECT_EQ(tree.get(2), left_node);
    EXPECT_EQ(tree.get(4), right_node);
    EXPECT_EQ(tree.get(1), left_left_node);
    EXPECT_EQ(tree.get(0), nullptr);
  }
}

TEST(BSTTest, TestInsert) {
  BST<int, int> tree;
  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(4, 4);

  auto root = tree.get_root();
  EXPECT_EQ(root->key, 3);
  EXPECT_EQ(root->left, tree.get(2));
  EXPECT_EQ(root->right, tree.get(4));
}

TEST(BSTTest, TestRemove) {
  BST<int, int> tree;
  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(4, 4);

  tree.remove(3);
  EXPECT_EQ(tree.get(3), nullptr);
  tree.remove(2);
  EXPECT_EQ(tree.get(2), nullptr);
}

TEST(BSTTest, TestFuzzRegression) {
  uint8_t data[] = {0xa5, 0xf7, 0x60, 0xee, 0x5a, 0xdf};
  size_t size = sizeof(data) / sizeof(data[0]);
  BST<uint8_t, int> tree;
  for (size_t i = 0; i < size; i++) {
    auto node = tree.get(data[i]);
    if (node == nullptr) {
      tree.insert(data[i], 0);
      node = tree.get(data[i]);
    }
    node->value++;
  }
  for (size_t i = 0; i < size; i++) {
    auto node = tree.get(data[i]);
    node->value--;
    if (node->value == 0)
      tree.remove(data[i]);
  }
  EXPECT_EQ(tree.get_root(), nullptr);
}

TEST(SortingTest, TestPartition) {
  int pivots[] = {17, 1, 1, 1};
  int arrs[][5] = {{0, 20, 2, 21, 4}, {0}, {0, 0}, {0, 2}};
  int lengths[] = {5, 1, 2, 2};
  for (int i = 0; i < 4; i++) {
    arrs[i][0] = pivots[i];
    int len = lengths[i];
    int pivot_pos = partition(arrs[i], 0, len - 1);
    EXPECT_EQ(pivots[i], arrs[i][pivot_pos]);
    for (int j = 0; j < len; j++) {
      if (j <= pivot_pos)
        EXPECT_TRUE(arrs[i][j] <= pivots[i]);
      else
        EXPECT_TRUE(arrs[i][j] > pivots[i]);
    }
  }
}

TEST(SortingTest, TestMerge) {
  int arr[] = {17, 20, 2, 21, 4};
  merge_sort(arr, 0, 4);
  for (int i = 1; i < 5; i++)
    EXPECT_TRUE(arr[i - 1] <= arr[i]);
}

TEST(AVLTreeTest, TestGet) {
  auto root = new AVLNode<int, int>();
  root->key = 3;
  root->value = 3;
  root->height = 2;
  auto left_node = new AVLNode<int, int>();
  left_node->key = 2;
  left_node->value = 2;
  left_node->height = 1;
  auto right_node = new AVLNode<int, int>();
  right_node->key = 4;
  right_node->value = 4;
  right_node->height = 0;

  root->left = left_node;
  root->right = right_node;

  auto left_left_node = new AVLNode<int, int>();
  left_left_node->key = 1;
  left_left_node->value = 1;
  left_left_node->height = 0;

  left_node->left = left_left_node;

  AVLTree<int, int> tree(root);
  EXPECT_EQ(tree.get_root(), root);
  EXPECT_EQ(tree.get(2), left_node);
  EXPECT_EQ(tree.get(4), right_node);
  EXPECT_EQ(tree.get(1), left_left_node);
  EXPECT_EQ(tree.get(0), nullptr);
}

TEST(AVLTreeTest, TestRotate) {
  auto root = new AVLNode<int, int>();
  root->key = 3;
  root->value = 3;
  root->height = 2;
  auto left_node = new AVLNode<int, int>();
  left_node->key = 2;
  left_node->value = 2;
  left_node->height = 1;
  auto right_node = new AVLNode<int, int>();
  right_node->key = 4;
  right_node->value = 4;
  right_node->height = 0;

  root->left = left_node;
  root->right = right_node;

  auto left_left_node = new AVLNode<int, int>();
  left_left_node->key = 1;
  left_left_node->value = 1;
  left_left_node->height = 0;

  left_node->left = left_left_node;

  AVLTree<int, int> tree(root);
  tree.ll_rotate(root);
  EXPECT_EQ(tree.get_root()->key, 2);
  EXPECT_EQ(tree.get_root()->left->key, 1);
  EXPECT_EQ(tree.get_root()->right->key, 3);
  EXPECT_EQ(tree.get_root()->right->right->key, 4);
  EXPECT_EQ(tree.get_root()->height, 2);
  EXPECT_EQ(tree.get_root()->left->height, 0);
  EXPECT_EQ(tree.get_root()->right->height, 1);
  EXPECT_EQ(tree.get_root()->right->right->height, 0);
}

TEST(AVLTreeTest, TestInsert) {
  AVLTree<int, int> tree;
  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(1, 1);
  tree.insert(4, 4);
  tree.insert(5, 5);
  tree.insert(6, 6);
  tree.insert(7, 7);
  EXPECT_EQ(tree.get_root()->key, 4);
  EXPECT_EQ(tree.get_root()->left->key, 2);
  EXPECT_EQ(tree.get_root()->right->key, 6);
  EXPECT_EQ(tree.get_root()->left->left->key, 1);
  EXPECT_EQ(tree.get_root()->left->right->key, 3);
  EXPECT_EQ(tree.get_root()->right->left->key, 5);
  EXPECT_EQ(tree.get_root()->right->right->key, 7);
  EXPECT_EQ(tree.get_root()->height, 2);
  EXPECT_EQ(tree.get_root()->left->height, 1);
  EXPECT_EQ(tree.get_root()->right->height, 1);
  EXPECT_EQ(tree.get_root()->left->left->height, 0);
  EXPECT_EQ(tree.get_root()->left->right->height, 0);
  EXPECT_EQ(tree.get_root()->right->left->height, 0);
  EXPECT_EQ(tree.get_root()->right->right->height, 0);
  tree.insert(16, 16);
  tree.insert(15, 15);
  EXPECT_EQ(tree.get_root()->right->right->key, 15);
  EXPECT_EQ(tree.get_root()->right->right->left->key, 7);
  EXPECT_EQ(tree.get_root()->right->right->right->key, 16);
}

TEST(AVLTreeTest, TestRemove) {
  AVLTree<int, int> tree;
  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(1, 1);
  tree.insert(4, 4);
  tree.insert(5, 5);
  tree.insert(6, 6);
  tree.insert(7, 7);
  tree.remove(4);
  tree.remove(6);
  tree.remove(7);
  EXPECT_EQ(tree.get_root()->key, 2);
  EXPECT_EQ(tree.get_root()->left->key, 1);
  EXPECT_EQ(tree.get_root()->right->key, 5);
  EXPECT_EQ(tree.get_root()->right->left->key, 3);
}

TEST(AVLTreeTest, TestPASample) {
  AVLTree<int, int> tree;
  tree.insert(4, 4);
  tree.insert(2, 2);
  tree.insert(10, 10);
  tree.insert(9, 9);
  tree.insert(15, 15);
  tree.insert(5, 5);
  tree.insert(0, 0);
  tree.remove(4);
  EXPECT_EQ(tree.get_root()->key, 9);
  EXPECT_EQ(tree.get_root()->left->key, 2);
  EXPECT_EQ(tree.get_root()->right->key, 10);
  EXPECT_EQ(tree.get_root()->left->left->key, 0);
  EXPECT_EQ(tree.get_root()->left->right->key, 5);
  EXPECT_EQ(tree.get_root()->right->right->key, 15);
}

TEST(UnionFindTest, TestUnion) {
  {
    UnionFind uf(5);
    EXPECT_FALSE(uf.is_same_set(0, 1));
    uf.union_set(0, 1);
    EXPECT_TRUE(uf.is_same_set(0, 1));
  }
  {
    UnionFind uf(100);
    for (int i = 1; i < 100; i++)
      uf.union_set(0, i);
    for (int i = 0; i < 100; i++)
      EXPECT_TRUE(uf.is_same_set(0, i));
  }
}

TEST(VectorTest, TestInit) {
  Vector<int> vec(10, 42);
  for (int i = 0; i < 10; i++)
    EXPECT_EQ(vec[i], 42);
  EXPECT_EQ(vec.size(), 10);
  vec[0] = 0;
  EXPECT_EQ(vec[0], 0);
}

TEST(VectorTest, TestPush) {
  Vector<int> vec;
  for (int i = 0; i < 10; i++)
    vec.push_back(i);
  EXPECT_EQ(vec.size(), 10);
  for (int i = 0; i < 10; i++)
    EXPECT_EQ(vec[i], i);
}

TEST(VectorTest, TestClear) {
  Vector<int> vec(10, 42);
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, TestAssign) {
  Vector<int> vec;
  vec.assign(10, 42);
  for (int i = 0; i < 10; i++)
    EXPECT_EQ(vec[i], 42);
}
