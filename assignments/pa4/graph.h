#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include <deque.h>          // expand: true
#include <priority_queue.h> // expand: true
#include <utils.h>          // expand: true

// TODO: remove training wheels
#include <unordered_map>
#include <vector>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

struct Edge {
  int weight, dest, src;
  string label;
  bool finite;

  Edge() : weight(0), dest(0), label(), finite(true) {}
  Edge(int weight, int id) : weight(weight), dest(id), label(), finite(true) {}
  Edge(int weight, int id, const string &label)
      : weight(weight), dest(id), label(label), finite(true) {}
  Edge(bool finite, int id, const string &label)
      : weight(0), dest(id), label(label), finite(finite) {}
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
      return Edge(false, another.dest, "");
    return Edge(this->weight + another.weight, another.dest);
  }
};

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph() : label_count(0), label_id_table(), labels(), graph{} {};
  ~Graph(){};

  string DFS();
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

  class LabelComparator {
  private:
    const Graph &parent;

  public:
    LabelComparator(const Graph &parent);
    int operator()(const Edge &edge1, const Edge &edge2) const;
  };

  class WeightComparator {
  private:
    const Graph &parent;

  public:
    WeightComparator(const Graph &parent);
    int operator()(const Edge &edge1, const Edge &edge2) const;
  };

  int getNodeId(const string &label);
  int compareByLabel(const Edge &edge1, const Edge &edge2);
  void sortGraph();
  void sortGraph(vector<vector<Edge>> &graph);
  template <typename T> void sortEdges(vector<Edge> &arr, const T &comparator);
  template <typename T>
  void mergeArr(vector<Edge> &arr, const T &comparator, int lo, int mid,
                int hi);
  void dfsTraverse(int here_id, vector<bool> &visited, vector<int> &visit_seq);
  void countCycles(int here_id, int parent_id, vector<int> &parent,
                   vector<int> &visited, int &count);
  bool checkDag(int here_id, vector<int> &visited);
  void topologicalSort(int here_id, vector<bool> &visited,
                       Deque<int> &sort_result);
  void addAdjacent(int here_id, PriorityQueue<Edge> &pq, vector<bool> &added);

  int label_count;
  unordered_map<string, int> label_id_table;
  vector<string> labels;
  vector<vector<Edge>> graph;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
