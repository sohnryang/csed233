#include "double_linked_list.cpp"
#include <gtest/gtest.h>

TEST(DoubleLinkedListTest, TestInit) {
  DoubleLinkedList dl;
  EXPECT_EQ(dl.size(), 0);
  EXPECT_TRUE(dl.empty());
}

TEST(DoubleLinkedListTest, TestPush) {
  {
    DoubleLinkedList dl;
    for (int i = 0; i < 5; i++) {
      auto node = new TwoWayNode();
      node->info = i;
      dl.push_back(node);
    }
    EXPECT_EQ(dl.size(), 5);
    EXPECT_FALSE(dl.empty());
    for (int i = 0; i < 5; i++) {
      auto node = dl.get_index(i);
      EXPECT_EQ(node->info, i);
    }
  }

  {
    DoubleLinkedList dl;
    for (int i = 0; i < 5; i++) {
      auto node = new TwoWayNode();
      node->info = i;
      dl.push_front(node);
    }
    EXPECT_EQ(dl.size(), 5);
    EXPECT_FALSE(dl.empty());
    for (int i = 0; i < 5; i++) {
      auto node = dl.get_index(i);
      EXPECT_EQ(node->info, 4 - i);
    }
  }
}

TEST(DoubleLinkedListTest, TestIndex) {
  DoubleLinkedList dl;
  TwoWayNode *nodes[5];
  for (int i = 0; i < 5; i++) {
    auto node = new TwoWayNode();
    nodes[i] = node;
    node->info = i;
    dl.push_back(node);
  }
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(nodes[i], dl.get_index(i));
}

TEST(DoubleLinkedListTest, TestRemove) {
  {
    DoubleLinkedList dl;
    auto node = new TwoWayNode();
    node->info = 1;
    dl.push_back(node);
    EXPECT_EQ(dl.size(), 1);
    dl.remove(node);
    EXPECT_TRUE(dl.empty());
    delete node;
  }

  {
    DoubleLinkedList dl;
    for (int i = 0; i < 5; i++) {
      auto node = new TwoWayNode();
      node->info = i;
      dl.push_back(node);
      dl.remove(node);
      EXPECT_EQ(dl.size(), 0);
      EXPECT_TRUE(dl.empty());
    }
  }
}

TEST(DoubleLinkedListTest, TestInsert) {
  DoubleLinkedList dl;
  auto n = dl.get_index(1);
  EXPECT_EQ(n->info, 0);
  auto already_existed = TwoWayNode{-1, nullptr, nullptr};
  for (int i = 0; i < 2; i++) {
    auto node = new TwoWayNode(already_existed);
    dl.push_back(node);
  }
  auto node = new TwoWayNode();
  dl.insert(dl.head_node()->next_ptr->next_ptr, node);
  auto inserted = dl.get_index(1);
  EXPECT_EQ(inserted, node);
}
