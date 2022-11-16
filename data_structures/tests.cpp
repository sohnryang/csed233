#include <bitmask.h>
#include <bst.h>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <deque.h>
#include <double_linked_list.h>
#include <gtest/gtest.h>
#include <priority_queue.h>
#include <utility>

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
