struct TwoWayNode {
  int info;
  TwoWayNode *prev_ptr, *next_ptr;
};

class Queue {
private:
  TwoWayNode *head, *tail, *selected_prev, *selected_next;
  int element_count;

public:
  Queue();
  ~Queue();
  TwoWayNode *first_node() const;
  TwoWayNode *last_node() const;
  void push_front(const TwoWayNode &node);
  TwoWayNode *pop_back();
  int size() const;
};

Queue::Queue() : element_count(0) {
  this->head = new TwoWayNode();
  this->tail = new TwoWayNode();
  this->head->next_ptr = this->tail;
  this->tail->prev_ptr = this->head;
}

Queue::~Queue() {
  TwoWayNode *current = this->head;
  while (current) {
    TwoWayNode *next_node = current->next_ptr;
    delete current;
    current = next_node;
  }
}

TwoWayNode *Queue::first_node() const { return this->head->next_ptr; }

TwoWayNode *Queue::last_node() const { return this->tail->prev_ptr; }

void Queue::push_front(const TwoWayNode &node) {
  TwoWayNode *new_node = new TwoWayNode(node);
  new_node->next_ptr = this->head->next_ptr;
  new_node->prev_ptr = this->head;
  this->head->next_ptr->prev_ptr = new_node;
  this->head->next_ptr = new_node;
  this->element_count++;
}

TwoWayNode *Queue::pop_back() {
  TwoWayNode *popped = this->tail->prev_ptr;
  this->tail->prev_ptr = popped->prev_ptr;
  popped->prev_ptr->next_ptr = this->tail;
  this->element_count--;
  return popped;
};

int Queue::size() const { return this->element_count; }
