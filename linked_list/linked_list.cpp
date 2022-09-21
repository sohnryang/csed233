#include <iostream>
#include <ostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;

enum Commands {
  PrintAll = 0,
  PrintSelected = 1,
  Select = 2,
  NextNode = 3,
  Insert = 4,
  Remove = 5,
  Size = 6,
  Quit = -1
};

struct Node {
  int info;
  Node *next_ptr;
};

ostream &operator<<(ostream &os, Node const &node) {
  return os << "{info: " << node.info << "}";
}

class LinkedList {
private:
  Node *head;
  Node *selected_before;

public:
  LinkedList();
  ~LinkedList();
  Node *first_node() const;
  Node *get_selected() const;
  void select_next();
  void select_index(int index);
  void insert(const Node &node);
  void remove();
  int size() const;
};

LinkedList::LinkedList() {
  this->head = new Node();
  this->selected_before = this->head;
}

LinkedList::~LinkedList() {
  Node *current_node = this->head;
  while (current_node) {
    Node *next_node = current_node->next_ptr;
    delete current_node;
    current_node = next_node;
  }
}

Node *LinkedList::get_selected() const {
  return this->selected_before->next_ptr;
}

Node *LinkedList::first_node() const { return this->head->next_ptr; }

void LinkedList::select_next() {
  this->selected_before = this->selected_before->next_ptr;
}

void LinkedList::select_index(int index) {
  this->selected_before = this->head;
  for (int i = 0; i < index; ++i)
    this->select_next();
}

void LinkedList::insert(const Node &node) {
  Node *new_node = new Node(node);
  new_node->next_ptr = this->selected_before->next_ptr;
  this->selected_before->next_ptr = new_node;
}

void LinkedList::remove() {
  Node *deleted_node = this->selected_before->next_ptr;
  this->selected_before->next_ptr = deleted_node->next_ptr;
  delete deleted_node;
}

int LinkedList::size() const {
  int result = 0;
  Node *current = this->first_node();
  while (current) {
    result++;
    current = current->next_ptr;
  }
  return result;
}

int main() {
  LinkedList ls;
  bool quit_loop = false;
  while (!quit_loop) {
    int cmd;
    cin >> cmd;
    switch (cmd) {
    case Commands::PrintAll: {
      Node *current = ls.first_node();
      while (current) {
        cout << "Node@" << (void *)current << ": " << *current << endl;
        current = current->next_ptr;
      }
      break;
    }
    case Commands::PrintSelected: {
      Node *node = ls.get_selected();
      if (node == nullptr) {
        break;
      }
      cout << "Node@" << (void *)node << ": " << *node << endl;
      break;
    }
    case Commands::Select: {
      int index;
      cin >> index;
      ls.select_index(index);
      break;
    }
    case Commands::NextNode:
      ls.select_next();
      break;
    case Commands::Insert: {
      int info;
      cin >> info;
      Node node{info, nullptr};
      ls.insert(node);
      break;
    }
    case Commands::Remove:
      ls.remove();
      break;
    case Commands::Size:
      cout << ls.size() << endl;
      break;
    case Commands::Quit:
      quit_loop = true;
      break;
    default:
      cout << "Unknown command: " << cmd << endl;
    }
  }
  return 0;
}
