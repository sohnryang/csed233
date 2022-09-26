#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Choose the TIGHT bound of the following arraySum function

    *arraySum*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n >= 1 integers
        Output
        - int: Sum of given array A
        int arraySum(int n, int* A) {
            int currSum = 0;
            for (int i = 0; i < n; i++)
                currSum += A[i];
            return currSum;
        }


    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
  int answer = 2; // TODO: Change to your answer

  fout << "[Task 1]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 2] Choose the TIGHT bound of the following primeSearch function

    *primeSearch*
        Input
        - int num1: input number for starting range
        - int num2: input number for ending range
        Output
        - int numPrimes: The total number of prime numbers between num1 and num2
        int primeSearch(int num1, int num2) {
            int numPrimes = 0;
            int ctr = 0;
            for (int i = num1; i <= num2; i++) {
                for(int j = 2; j <= sqrt(i); j++) {
                    if(i % j == 0) {
                        ctr++;
                        break;
                    }
                }
                if(ctr == 0 && i > 1)
                    numPrimes++;
                ctr=0;
            }
            return numPrimes;
        }


    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n )
        4: O( n^2 )
*/
void task_2(ofstream &fout) {
  int answer = 4; // TODO: Change to your answer

  fout << "[Task 2]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the list.
        An user can insert or delete an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,index): insert “# of elements in the current list” at the
   index in the list. index indicates zero-based index.
        - (‘delete’,index): delete an element at the index in the list. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/
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

void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int size = 0;
  bool failed = false;
  LinkedList ls;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int index = instr_seq->instructions[i].value;
    if (command.compare("insert") == 0) {
      if (index < 0 || index > size) {
        failed = true;
        break;
      }
      ls.select_index(index);
      Node new_node{size, nullptr};
      ls.insert(new_node);
      size++;
    } else if (command.compare("delete") == 0) {
      if (index < 0 || index >= size) {
        failed = true;
        break;
      }
      ls.select_index(index);
      ls.remove();
      size--;
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  if (failed)
    answer = "error";
  else {
    ls.select_index(0);
    for (int i = 0; i < size; ++i) {
      Node *node = ls.get_selected();
      if (i != 0)
        answer += " ";
      answer += to_string(node->info);
      ls.select_next();
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   stack is empty, and the “top” operation is called, then print “-1”, If “pop”
   operation from the empty stack then print “error”

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack (integer is
   always positive)
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack
*/

void task_4(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  LinkedList ls;
  bool failed = false;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int arg = instr_seq->instructions[i].value;
    if (command.compare("push") == 0) {
      Node new_node{arg, nullptr};
      ls.insert(new_node);
    } else if (command.compare("pop") == 0) {
      Node *popped = ls.get_selected();
      if (!popped) {
        failed = true;
        break;
      }
      ls.remove();
    } else if (command.compare("top") == 0) {
      Node *top = ls.get_selected();
      if (!answer.empty())
        answer += " ";
      if (!top)
        answer += to_string(-1);
      else
        answer += to_string(top->info);
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (failed)
    answer = "error";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Queue

    Description:
        Implement a function which shows the value of a queue after the sequence
   of arbitrary queue operation. If the queue after the operations is empty,
   print “empty”. If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the queue from the head to the tail, in a string separated
   with spacebar
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on an empty queue
*/

struct TwoWayNode {
  int info;
  TwoWayNode *prev_ptr, *next_ptr;
};

class Queue {
private:
  TwoWayNode *head, *tail, *selected_prev, *selected_next;

public:
  Queue();
  ~Queue();
  TwoWayNode *last_node() const;
  void push_front(const TwoWayNode &node);
  TwoWayNode *pop_back();
};

Queue::Queue() {
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

TwoWayNode *Queue::last_node() const { return this->tail->prev_ptr; }

void Queue::push_front(const TwoWayNode &node) {
  TwoWayNode *new_node = new TwoWayNode(node);
  new_node->next_ptr = this->head->next_ptr;
  new_node->next_ptr->prev_ptr = new_node;
  new_node->prev_ptr = this->head;
  this->head->next_ptr = new_node;
}

TwoWayNode *Queue::pop_back() {
  TwoWayNode *popped = this->tail->prev_ptr;
  this->tail->prev_ptr = popped->prev_ptr;
  popped->prev_ptr->next_ptr = this->tail;
  return popped;
};

void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  Queue q;
  int size = 0;
  bool failed = false;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;

    if (command.compare("enqueue") == 0) {
      TwoWayNode node{value, nullptr, nullptr};
      q.push_front(node);
      size++;
    } else if (command.compare("dequeue") == 0) {
      if (size == 0) {
        failed = true;
        break;
      }
      auto popped = q.pop_back();
      delete popped;
      size--;
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (failed)
    answer = "error";
  else if (size == 0)
    answer = "empty";
  else {
    for (int i = 0; i < size; ++i) {
      if (i != 0)
        answer += " ";
      auto popped = q.pop_back();
      answer += to_string(popped->info);
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Circular Queue

    Description:
        - a.	Implement a function which shows the value in the circular queue
   from the head to tale. If “enqueue” operates on full or “dequeue” operates
   on an empty queue, no change would happen.

    Input:
        Sequence of commands, which is one of the following,
        -(‘enqueue’,integer): enqueue integer into the current queue
        -(‘dequeue’,NULL): dequeue integer into the current queue

    Output:
        - Values in the queue from the head to the tail, in a size of 4.
   string separated with the spacebar, empy memory shows NULL -	No
   pointer movement if dequeue on empty, enqueue on full queue

*/

void task_6(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;
  int queue_size = 4;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int *q = new int[queue_size];
  int size = 0, lo = 0, hi = 0;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("enqueue") == 0) {
      if (size == 4)
        continue;
      q[hi] = value;
      hi = (hi + 1) % queue_size;
      size++;
    } else if (command.compare("dequeue") == 0) {
      if (size == 0)
        continue;
      lo = (lo + 1) % queue_size;
      size--;
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  for (int i = 0; i < size; ++i) {
    if (i != 0)
      answer += " ";
    answer += to_string(q[lo]);
    lo = (lo + 1) % queue_size;
  }
  delete[] q;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 6]" << endl;
  fout << answer << endl;
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    try {
      instr_seq = ParseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 0:
    task_1(fout);

    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq_4);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
