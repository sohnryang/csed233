struct TwoWayNode {
  int info;
  TwoWayNode *prev_ptr, *next_ptr;
};

class DoubleLinkedList {
private:
  TwoWayNode *head, *tail;

public:
  DoubleLinkedList();
  ~DoubleLinkedList();
  int size() const;
  bool empty() const;
  TwoWayNode *head_node() const;
  TwoWayNode *tail_node() const;
  TwoWayNode *get_index(int index) const;
  void insert(TwoWayNode *place, TwoWayNode *inserted);
  void push_front(TwoWayNode *node);
  void push_back(TwoWayNode *node);
  void remove(TwoWayNode *node);
};

DoubleLinkedList::DoubleLinkedList() {
  this->head = new TwoWayNode();
  this->tail = new TwoWayNode();
  this->head->next_ptr = this->tail;
  this->tail->prev_ptr = this->head;
}

DoubleLinkedList::~DoubleLinkedList() {
  auto current = this->head_node();
  while (current) {
    auto next_node = current->next_ptr;
    delete current;
    current = next_node;
  }
}

int DoubleLinkedList::size() const {
  int result = 0;
  auto current = this->head->next_ptr;
  while (current != this->tail) {
    result++;
    current = current->next_ptr;
  }
  return result;
}

bool DoubleLinkedList::empty() const {
  return this->head->next_ptr == this->tail;
}

TwoWayNode *DoubleLinkedList::head_node() const { return this->head; }
TwoWayNode *DoubleLinkedList::tail_node() const { return this->tail; }

TwoWayNode *DoubleLinkedList::get_index(int index) const {
  auto selected = this->head_node()->next_ptr;
  for (int i = 0; i < index; i++)
    selected = selected->next_ptr;
  return selected;
}

void DoubleLinkedList::insert(TwoWayNode *place, TwoWayNode *inserted) {
  auto before = place->prev_ptr, after = place;
  inserted->prev_ptr = before;
  inserted->next_ptr = after;
  before->next_ptr = inserted;
  after->prev_ptr = inserted;
}

void DoubleLinkedList::push_front(TwoWayNode *node) {
  this->insert(this->head_node()->next_ptr, node);
}

void DoubleLinkedList::push_back(TwoWayNode *node) {
  this->insert(this->tail_node(), node);
}

void DoubleLinkedList::remove(TwoWayNode *node) {
  auto before = node->prev_ptr, after = node->next_ptr;
  before->next_ptr = after;
  after->prev_ptr = before;
}
