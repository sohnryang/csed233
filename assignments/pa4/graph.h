#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include <deque.h> // expand: true

// TODO: remove training wheels
#include <unordered_map>
#include <vector>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

struct Edge {
  int weight, id;
  string label;
  bool finite;

  Edge() : weight(0), id(0), label(), finite(true) {}
  Edge(int weight, int id) : weight(weight), id(id), label(), finite(true) {}
  Edge(int weight, int id, const string &label)
      : weight(weight), id(id), label(label), finite(true) {}
  Edge(bool finite, int id, const string &label)
      : weight(0), id(id), label(label), finite(finite) {}
  bool operator<(const Edge &another) {
    if (!this->finite)
      return false;
    if (!another.finite)
      return true;
    if (this->weight < another.weight)
      return true;
    if (this->weight == another.weight && this->label < another.label)
      return true;
    return false;
  }
  Edge operator+(const Edge &another) {
    if (!this->finite || !another.finite)
      return Edge(false, another.id, "");
    return Edge(this->weight + another.weight, another.id);
  }
};

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph() : label_count(0), label_id_table(), labels(), graph{} {};
  ~Graph(){};

  string DFS();
  void sortGraph();
  string BFS();

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  int countUndirectedCycle();
  string getTopologicalSort();
  int countDirectedCycle();
  string getShortestPath(string source, string destination);
  string getAllShortestPaths();
  int primMST(ofstream &, string startNode);
  int kruskalMST(ofstream &);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  int getNodeId(const string &label);
  void sortByLabel(vector<Edge> &arr);
  void merge_arr(vector<Edge> &arr, int lo, int mid, int hi);
  void dfs_traverse(int here_id, vector<bool> &visited, vector<int> &visit_seq);
  void count_cycles(int here_id, int parent_id, vector<int> &parent,
                    vector<int> &visited, int &count);
  bool check_dag(int here_id, vector<int> &visited);
  void topological_sort(int here_id, vector<bool> &visited,
                        Deque<int> &sort_result);

  int label_count;
  unordered_map<string, int> label_id_table;
  vector<string> labels;
  vector<vector<Edge>> graph;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
