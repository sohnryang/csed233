/*
    Programming Assignment #3
*/
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

#include "avl.h"
#include "bst.h"
#include "closed_hash_function.h"
#include "closed_hash_table.h"
#include "open_hash_function.h"
#include "open_hash_table.h"
#include "sort.h"
#include "tree.h"
#include "utils.h"

using namespace std;

/*
    [Task 1] Quick Sort

    Description:
        Implement a function that sorts a given array using the Quick sort
   algorithm \\ with in-place partitioning in ascending order. Use the first
   element at the pivot. You can modify sort.cpp and sort.h files for this
   problem.

        TODO: Implement sortAlg::quickSort function

    Input:
        ('insertion',integer): insert integer into the array
        ('quickSort',NULL): sort the array using quick sort algorithm

    Output:
        Every value in the array whenever swapping happens including the initial
   step, \\ string separated with the white space (please use built-in function
   to print the array). You don’t need to consider exceptional cases such as
   overflow or an empty array. We will not test such cases.

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 1]" << endl;
  try {
    sortAlg sort;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("insertion") == 0) {
        sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
        sort.arr_size++;
      } else if (command.compare("quickSort") == 0) {
        sort.printArray(fout);
        sort.quickSort(fout, 0, sort.arr_size - 1);
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 2] Recursive Merge Sort

    Description:
        Implement a function that sorts a given array using the merge sort
        algorithm in ascending order using recursive merge sort.
        Split a list of elements into two sublists with the first sublist bigger
   than the second sublist, for a case when the input array has an odd number of
   elements. You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::mergeSort function
        TODO: Implement sortAlg::merge function

    Input:
        ('insert',integer): insert integer into the array
        ('mergeSort',NULL): sort the array using merge sort algorithm

    Output:
        Every value in the array for each sorting step including the initial
   step, string separated with the white space (please use built-in function to
   print the array). You don’t need to consider exceptional cases such as
   overflow or an empty array. We will not test such cases.
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 2]" << endl;
  try {
    sortAlg sort;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("insertion") == 0) {
        sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
        sort.arr_size++;
      } else if (command.compare("mergeSort") == 0) {
        sort.printArray(fout);
        sort.mergeSort(fout, 0, sort.arr_size - 1);
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 3] BST insertion / deletion

    Description:
        Implement a function that inserts and deletes an element into a BST.
        You can modify bst.cpp and bst.h files for this problem.

        TODO: Implementation BinarySearchTree::insertion function
        TODO: Implementation BinarySearchTree::deletion function

    Input of BinearySearchTree::insertion
        Key of the element to be inserted.

    Output of BinearySearchTree::insertion
        Return the -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of BinearySearchTree::deletion
        Key of the element to be deleted.

    Output of BinearySearchTree::deletion
        Return the -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    task_3 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 3]" << endl;
  try {
    BinarySearchTree tree;
    int ret;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int key = instr_seq.getInstruction(i).getValue();
      if (command.compare("insertion") == 0) {
        ret = tree.insertion(key);
        fout << ret << endl;
      } else if (command.compare("deletion") == 0) {
        ret = tree.deletion(key);
        fout << ret << endl;
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
    fout << tree.preOrder() << endl;
    fout << tree.inOrder() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 4] AVL tree insertion / deletion

    Description:
        Implement a function that inserts and deletes an element into a AVL
   tree. The insertion and deletion might cause the AVL tree to violate its
   properties (imbalance). Your code should be able to resolve the various
   imbalance type (LL, LR, RL, RR) of the AVL tree. You can modify avl.cpp and
   avl.h files for this problem.

        TODO: Implementation AVLTree::insertion function
        TODO: Implementation AVLTree::deletion function

        Hint : suggest you to call 'insertion' and 'deletion' function in
   BinarySearchTree class

    Input of AVLTree::insertion
        Key of the element to be inserted.

    Output of AVLTree::insertion
        Return -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of AVLTree::deletion function
        Key of the element to  deleted

    Output of AVLTree::deletion
        Return -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    task_4 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 4]" << endl;
  try {
    AVLTree tree;
    int ret;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int key = instr_seq.getInstruction(i).getValue();
      if (command.compare("insertion") == 0) {
        ret = tree.insertion(key);
        fout << ret << endl;
      } else if (command.compare("deletion") == 0) {
        ret = tree.deletion(key);
        fout << ret << endl;
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
    fout << tree.preOrder() << endl;
    fout << tree.inOrder() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 5] Open Hash table

    Description:
        Implement a open hash table with digit-folding-method.
        This hash table is used with integer keys \\
        and hashing into a table of size M
        Every component of the key is folded with size of 1(digit) \\
        and calculate their sum as described in our Lecture Note.
        This hash table uses singly linked list as a collision handling method.
        You don't need to consider the maximum length of linked list, deletion
   of a key \\ which does not exist or multiple insertions of the same key.
        You can modify open_hash_function.cpp, open_hash_function.h,
   open_hash_table.cpp \\ and open_hash_table.h files for this problem.


    Input: A sequence of commands
      - ('M',integer): The size of a hash table
                        (The first command is always 'M')
      - ('insert',int): Insert integer into the hash table
      - ('delete',int): Delete integer from the hash table

    Output: For each slot of the hash table, print out
      - the linked list, if the state of the slot is occupied
      - the state, if the state of the slot is empty
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 5]" << endl;
  try {
    int M;
    string key;
    OpenHashFunction *hf;
    OpenHashTable *ht;

    if (instr_seq.getLength() < 2 ||
        instr_seq.getInstruction(0).getCommand().compare("M") != 0) {
      cerr << "Invalid starting commands" << endl;
      exit(-1);
    }

    M = instr_seq.getInstruction(0).getValue();
    hf = new OpenHashFunction(M);
    ht = new OpenHashTable(M, hf);

    for (int i = 1; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int key = instr_seq.getInstruction(i).getValue();
      if (command.compare("insert") == 0) {
        ht->insert(key);
      } else if (command.compare("delete") == 0) {
        ht->erase(key);
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }

    ht->print_table(fout);

    delete ht;
    delete hf;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 6] Closed Hash table

    Description:
        Implement a closed hash table with rehashing implementation.
        This hash table is used with n-bit integer keys \\
        and hashing into a table of size 2^r, when r is even
        This hash table uses quadratic probing as a collision handling method.
        The index of the key k after i-th collision, h_i(k), is:
            h_i(k) = h(k) + i^2 + i + 1
        where h is the binary mid-square hash function.
        You can modify closed_hash_function.cpp, closed_hash_table.cpp, \\
        closed_hash_function.h and closed_hash_table.h files for this problem.

        TODO: Implementation ClosedHashTable::insert & ClosedHashTable::erase
   functions


    Input: A sequence of commands
      - ('n',integer): The size of a key
                       (The first command is always 'n')
      - ('r',integer): The size of an index
                       (The second command is always 'r')
      - ('insert',integer): Insert integer into the hash table
      - ('delete',integer): Delete integer from the hash table

    Output: For each slot of the hash table, print out
      - the value, if the state of the slot is occupied
      - the state, if the state of the slot is empty or deleted
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 6]" << endl;
  try {
    int n, r, key;
    ClosedHashFunction *hf;
    ClosedHashTable *ht;

    if (instr_seq.getLength() < 2 ||
        instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
        instr_seq.getInstruction(1).getCommand().compare("r") != 0) {
      cerr << "Invalid starting commands" << endl;
      exit(-1);
    }

    n = instr_seq.getInstruction(0).getValue();
    r = instr_seq.getInstruction(1).getValue();
    hf = new ClosedHashFunction(n, r);
    ht = new ClosedHashTable(pow(2, r), hf);

    for (int i = 2; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int key = instr_seq.getInstruction(i).getValue();
      if (command.compare("insert") == 0) {
        ht->insert(key);
      } else if (command.compare("delete") == 0) {
        ht->erase(key);
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }

    ht->print_table(fout);

    delete ht;
    delete hf;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence instr_seq;

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
      instr_seq.parseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout, instr_seq);
    break;
  case 2:
    task_2(fout, instr_seq);
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
    instr_seq.parseInstructions(TASK_1_DEFAULT_ARGUMENT);
    task_1(fout, instr_seq);

    instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
    task_2(fout, instr_seq);

    instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq);

    instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq);

    instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq);

    instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
