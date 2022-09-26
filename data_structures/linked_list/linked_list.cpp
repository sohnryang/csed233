struct Node {
  int info;
  Node *next_ptr;
};

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
