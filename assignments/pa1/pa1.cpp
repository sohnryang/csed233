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
        - int n: input number for ending range
        Output
        - int numPrimes: The total number of prime numbers less than n
        int primeSearch(int n) {
            int numPrimes = 0;
            int ctr = 0;
            for (int i = 0; i < n; i++) {
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
        3: O( n^(1/2) )
        4: O( n*n^(1/2) )
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

void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int size = 0;
  bool failed = false;
  DoubleLinkedList ls;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int index = instr_seq->instructions[i].value;
    if (command.compare("insert") == 0) {
      if (index < 0 || index > size) {
        failed = true;
        break;
      }
      auto place = ls.get_index(index);
      auto new_node = new TwoWayNode();
      new_node->info = size;
      ls.insert(place, new_node);
      size++;
    } else if (command.compare("delete") == 0) {
      if (index < 0 || index >= size) {
        failed = true;
        break;
      }
      auto removed = ls.get_index(index);
      ls.remove(removed);
      delete removed;
      size--;
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  if (failed)
    answer = "error";
  else if (size != 0) {
    auto node = ls.get_index(0);
    for (int i = 0; i < size; ++i) {
      if (i != 0)
        answer += " ";
      answer += to_string(node->info);
      node = node->next_ptr;
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

  DoubleLinkedList ls;
  bool failed = false;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int arg = instr_seq->instructions[i].value;
    if (command.compare("push") == 0) {
      auto new_node = new TwoWayNode();
      new_node->info = arg;
      ls.push_front(new_node);
    } else if (command.compare("pop") == 0) {
      if (ls.empty()) {
        failed = true;
        break;
      }
      auto top = ls.head_node()->next_ptr;
      ls.remove(top);
    } else if (command.compare("top") == 0) {
      if (!answer.empty())
        answer += " ";
      if (ls.empty()) {
        answer += "-1";
        continue;
      }
      auto top = ls.head_node()->next_ptr;
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

void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  DoubleLinkedList q;
  int size = 0;
  bool failed = false;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;

    if (command.compare("enqueue") == 0) {
      auto node = new TwoWayNode();
      node->info = value;
      q.push_back(node);
      size++;
    } else if (command.compare("dequeue") == 0) {
      if (size == 0) {
        failed = true;
        break;
      }
      auto popped = q.head_node()->next_ptr;
      q.remove(popped);
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
    auto node = q.head_node()->next_ptr;
    for (int i = 0; i < size; ++i) {
      if (i != 0)
        answer += " ";
      answer += to_string(node->info);
      node = node->next_ptr;
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
