/*
    Programming Assignment #6
*/
#include "graph.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

/*
    [Task 1] Undirected Graph - Graph Traversals

    Description:
        Implement a function that finds DFS traverse from the given undirected
   graph. The graph may consist of several connected graphs. The search starts
   with the node coming first in the lexicographical order of labels. Also, the
   next node should be selected in lexicographical order among connected nodes.
        If there exist n connected graphs, then print n traverses separated with
   a newline in lexicographical order.

        TODO: Implement Graph::addUndirectedEdge, Graph::DFS and Graph::BFS
   functions

    Input & output
    Input: Pairs of nodes with alphabet labels that indicate edges.
        - ('A','B'): an edge between node A and node B.
        - ('End','DFS') or ('End','BFS'):String representing traverse mode.
    Output:
        - Result of traverse separated with a white space
        - Multiple traverses are separated with a new line, in lexicographical
   order.

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 1]" << endl;

  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength() - 1; i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addUndirectedEdge(firstNode, secondNode);
    }
    string search =
        instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();
    if (search.compare("DFS") == 0)
      fout << graph.DFS() << endl;
    else if (search.compare("BFS") == 0)
      fout << graph.BFS() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 2] Undirected Graph - Cycle Count

    Description:
        Implement a function that returns the number of cycles in the given
   undirected graph. A cycle is a non-empty path in which the only repeated
   vertices are the first and last vertices. Note that any subset of vertices of
   a cycle does not form another cycle (that is, do not count inner-cycles). You
   can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge, which is implemented at the
   task 1, and Graph::countUndirectedCycle functions.

    Input & output
    Input: Pairs of node labels that indicate edges.
        - ('A', 'B'): an edge between node A and node B.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - The number of cycles in the given undirected graph
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 2]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addUndirectedEdge(firstNode, secondNode);
    }
    fout << graph.countUndirectedCycle() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 3] Directed Graph - Topological Sort

    Description:
        Implement a function that performs a topological sort using the given
   directed graph. If there exists more than one result, print the topological
   sort that comes first in the ascending order. To take an example below,
   acceptable topological sorts are ‘A B C D F E’, ‘A C B F E D’, ‘A C D B F E’,
   etc. Among these, the desirable output is ‘A B C D F E’. Also, print ‘error’
   if the topological sort could not be performed. You can modify graph.cpp and
   graph.h files for this problem.

        TODO: Implement Graph::addDirectedEdge and Graph::getTopologicalSort
   functions

    Input & output
    Input: Pairs of node labels that indicate edges.
        - ('A', 'B'): an edge from node A to node B.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - Topological sort or 'error'
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 3]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addDirectedEdge(firstNode, secondNode);
    }
    fout << graph.getTopologicalSort() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 4] Directed Graph - Cycle Count

    Description:
        Implement a function that returns the number of cycles in the given
   directed graph. A cycle is a non-empty path in which the only repeated
   vertices are the first and last vertices. Unlike an undirected graph, the
   edges of the graph have direction in this time. For instance, (‘A’,’B’) is
   different from (‘B’,’A’). You can modify graph.cpp and graph.h files for this
   problem.

        TODO: Implement Graph::addDirectedEdge, which is implemented at the task
   3, and Graph::countDirectedCycle functions.

    Input & output
    Input: Pairs of node labels that indicate edges.
        - ('A', 'B'): an edge from node A to node B.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - The number of cycles in the given directed graph
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 4]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addDirectedEdge(firstNode, secondNode);
    }
    fout << graph.countDirectedCycle() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 5] Dijkstra's Algorithm

    Description:
        Implement a function that finds the shortest path from the source node
   to the destination node in the given graph. We assume that the given graph is
   a directed, weighted, and weakly-connected graph. All weights of edges are
   positive (i.e. larger than 0). This function should return the sequence of
   node labels along the path and also the length (sum of the weights of the
   edges) of the path. If the path from the source node to the destination node
   doesn't exist, return 'error'. You can modify the graph.cpp and graph.h files
   for this problem.

        TODO: Implement Graph::addDirectedEdge and Graph::getShortestPath
   functions

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge from node A to node B with weight value
   {integer}.
        - ('A', 'B'): a pair of node labels that indicates the source and the
   destination node. The first element indicates the source node and the second
   one indicates the destination node. Output:
        - A sequence of the node labels along the path followed by length of the
   path.
        - error if the path does not exist
 */

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 5]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength() - 1; i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int value = instr_seq.getInstruction(i).getValue();
      string firstNode = command.substr(0, command.find('-'));
      string secondNode =
          command.substr(command.find('-') + 1, command.length());
      graph.addDirectedEdge(firstNode, secondNode, value);
    }
    string source =
        instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
    string destination =
        instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();
    fout << graph.getShortestPath(source, destination) << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 6] Floyd's Algorithm

    Description:
        Implement a function that finds the shortest paths of all pairs of nodes
   in the given graph. Unlike problem 3, there will be an edge(s) with negative
   weight value(s). This function should return the distances of all paths in
   the given graph like the above image. The nodes are sorted in lexicographical
   order in the distance matrix. If the source and the destination is identical,
   distance is 0. If there is no path from the source to the destination,
   distance is INF. You can modify the graph.cpp and graph.h files for this
   problem.

        TODO: Implement Graph::addDirectedEdge and Graph::getAllShortestPaths
   function

    Input & Output
    Input: A sequence of commands
        - ('A-B', integer): an edge from node A to node B with weight value
   {integer}. Output:
        - A distance matrix in string format.
          The nodes in the row and column of the matrix are sorted in
   lexicographic order. If the source and the destination node are same, the
   distance is 0. If the path doesn't exist, the distance is INF.
 */

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 6]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int value = instr_seq.getInstruction(i).getValue();
      string firstNode = command.substr(0, command.find('-'));
      string secondNode =
          command.substr(command.find('-') + 1, command.length());
      graph.addDirectedEdge(firstNode, secondNode, value);
    }
    fout << graph.getAllShortestPaths() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 7] Prim's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of
   the given weighted undirected graph using the Prim's algorithm. Given a start
   node, this function start with the single-vertex tree of the given node.
        Then, the function prints the added edge and the weight of the edge each
   time the tree grows. When printing an edge, you first have to print the label
   of the node that already exists in the tree, then print the label of the node
   that newly inserted into the tree. If there are multiple edges with the same
   weight, this function checks the label of the added node (i.e. the node which
   is not included in the tree) and selects the node with the first label in
   lexicographical order. Finally, the function returns the cost of the MST
   (i.e. the sum of edge weights). You can assume that the given graph is a
   connected graph. You can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::primMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge between node A and node B with weight value
   {integer}.
        - ('MST', 'A'): find MST using the Prim's algorithm which start with
   node A. Output:
        - For each time the tree grows, print the labels of the nodes indicating
   the added edges and the weight of the edge as a string separated with a white
   space.
        - Print the cost of MST.
*/

void task_7(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 7]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("MST") == 0) {
        string startNode = instr_seq.getInstruction(i).getValueStr();
        fout << graph.primMST(fout, startNode) << endl;
      } else {
        string firstNode = command.substr(0, command.find('-'));
        string secondNode =
            command.substr(command.find('-') + 1, command.length());
        int value = instr_seq.getInstruction(i).getValue();
        graph.addUndirectedEdge(firstNode, secondNode, value);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 8] Kruskal's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of
   the given weighted undirected graph using the Kruskal's algorithm. The
   function prints the added edge and the weight of the edge each time the tree
   grows. When printing an edge, you have to print the label in lexicographical
   order. If there are multiple edges with the same weight, this function also
   selects the edge in lexicographical order. That means it compares the first
   node of edges, and if the first node is the same, it compares the second node
   of edges. The function return the cost of the MST (i.e. the sum of edge
   weights). You can assume that the given graph is a connected graph. You can
   modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::kruskalMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge between node A and node B with weight value
   {integer}.
        - ('MST', NULL): find MST using the Kruskal's algorithm.
    Output:
        - For each time the tree grows, print the labels of the nodes indicating
   the added edges in lexicographical order and the weight of the edge as a
   string separated with a white space.
        - Print the cost of MST.
*/

void task_8(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 8]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("MST") == 0) {
        fout << graph.kruskalMST(fout) << endl;
      } else {
        string firstNode = command.substr(0, command.find('-'));
        string secondNode =
            command.substr(command.find('-') + 1, command.length());
        int value = instr_seq.getInstruction(i).getValue();
        graph.addUndirectedEdge(firstNode, secondNode, value);
      }
    }
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
  case 7:
    task_7(fout, instr_seq);
    break;
  case 8:
    task_8(fout, instr_seq);
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

    instr_seq.parseInstructions(TASK_7_DEFAULT_ARGUMENT);
    task_7(fout, instr_seq);

    instr_seq.parseInstructions(TASK_8_DEFAULT_ARGUMENT);
    task_8(fout, instr_seq);

    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
