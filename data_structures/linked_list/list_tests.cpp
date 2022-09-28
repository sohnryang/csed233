#include "double_linked_list.cpp"
#include <gtest/gtest.h>

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
