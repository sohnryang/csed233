#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

#include <deque.h> // expand: true
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

int Graph::getNodeId(const string &label) {
  int id;
  if (label_id_table.count(label))
    id = label_id_table[label];
  else {
    id = label_count++;
    label_id_table[label] = id;
    labels.push_back(label);
    graph.push_back({});
  }
  return id;
}

void Graph::merge_arr(vector<Edge> &arr, int lo, int mid, int hi) {
  std::vector<Edge> left_arr(mid - lo), right_arr(hi - mid);
  for (int i = 0; i < mid - lo; i++)
    left_arr[i] = arr[lo + i];
  for (int i = 0; i < hi - mid; i++)
    right_arr[i] = arr[mid + i];
  int left_idx = 0, right_idx = 0, arr_idx = lo;
  while (left_idx < mid - lo && right_idx < hi - mid) {
    if (labels[left_arr[left_idx].id] < labels[right_arr[right_idx].id])
      arr[arr_idx++] = left_arr[left_idx++];
    else
      arr[arr_idx++] = right_arr[right_idx++];
  }
  while (left_idx < mid - lo)
    arr[arr_idx++] = left_arr[left_idx++];
  while (right_idx < hi - mid)
    arr[arr_idx++] = right_arr[right_idx++];
}

void Graph::sortByLabel(vector<Edge> &arr) {
  for (int subarr_size = 1; subarr_size < arr.size(); subarr_size *= 2) {
    for (int lo = 0; lo < arr.size(); lo += 2 * subarr_size) {
      int mid = std::min(lo + subarr_size, (int)arr.size()),
          hi = std::min(mid + subarr_size, (int)arr.size());
      merge_arr(arr, lo, mid, hi);
    }
  }
}

void Graph::dfs_traverse(int here_id, vector<bool> &visited,
                         vector<int> &visit_seq) {
  visited[here_id] = true;
  visit_seq.push_back(here_id);
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].id;
    if (!visited[there_id])
      dfs_traverse(there_id, visited, visit_seq);
  }
}

void Graph::sortGraph() {
  for (int i = 0; i < label_count; i++)
    sortByLabel(graph[i]);
}

void Graph::count_cycles(int here_id, int parent_id, vector<int> &parent,
                         vector<int> &visited, int &count) {
  visited[here_id] = 1;
  parent[here_id] = parent_id;
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].id;
    if (parent[here_id] == there_id)
      continue;
    if (visited[there_id] == 2)
      continue;
    if (visited[there_id] == 1) {
      count++;
      continue;
    }
    count_cycles(there_id, here_id, parent, visited, count);
  }
  visited[here_id] = 2;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string Graph::DFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  vector<Edge> nodes(label_count);
  for (int i = 0; i < label_count; i++)
    nodes[i] = Edge(0, i);
  sortByLabel(nodes);
  sortGraph();
  vector<bool> visited(label_count, false);
  vector<int> visit_seq;
  string result;
  for (int i = 0; i < label_count; i++) {
    int here_id = nodes[i].id;
    if (visited[here_id])
      continue;
    if (!result.empty())
      result += "\n";
    dfs_traverse(here_id, visited, visit_seq);
    for (int i = 0; i < visit_seq.size(); i++) {
      if (i != 0)
        result += " ";
      result += labels[visit_seq[i]];
    }
    visit_seq.clear();
  }
  return result;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::BFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  vector<Edge> nodes(label_count);
  for (int i = 0; i < label_count; i++)
    nodes[i] = Edge(0, i);
  sortByLabel(nodes);
  sortGraph();
  vector<bool> visited(label_count, false);
  string result;
  for (int i = 0; i < label_count; i++) {
    int start_id = nodes[i].id;
    if (visited[start_id])
      continue;
    Deque<int> queue;
    queue.push_back(start_id);
    visited[start_id] = true;
    string line = labels[start_id];
    while (!queue.empty()) {
      int here_id = queue.pop_front();
      for (int j = 0; j < graph[here_id].size(); j++) {
        int there_id = graph[here_id][j].id;
        if (visited[there_id])
          continue;
        queue.push_back(there_id);
        visited[there_id] = true;
        line += " ";
        line += labels[there_id];
      }
    }
    if (!result.empty())
      result += "\n";
    result += line;
  }
  return result;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int nodeA_id = getNodeId(nodeA), nodeB_id = getNodeId(nodeB);
  addDirectedEdge(nodeA, nodeB, 0);
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int nodeA_id = getNodeId(nodeA), nodeB_id = getNodeId(nodeB);
  for (int i = 0; i < graph[nodeA_id].size(); i++) {
    if (graph[nodeA_id][i].id != nodeB_id)
      continue;
    graph[nodeA_id][i].weight = min(weight, graph[nodeA_id][i].weight);
    return 0;
  }
  graph[nodeA_id].push_back(Edge(weight, nodeB_id));
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  addDirectedEdge(nodeA, nodeB);
  addDirectedEdge(nodeB, nodeA);
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  addDirectedEdge(nodeA, nodeB, weight);
  addDirectedEdge(nodeB, nodeA, weight);
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countUndirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  vector<int> visited(label_count, 0), parent(label_count, -1);
  int count = 0;
  for (int i = 0; i < label_count; i++) {
    if (visited[i] == 2)
      continue;
    count_cycles(i, -1, parent, visited, count);
    for (int j = 0; j < label_count; j++)
      if (visited[j] == 1)
        visited[j] = 2;
  }
  return count;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getTopologicalSort() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "";
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countDirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getShortestPath(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string Graph::getAllShortestPaths() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return "";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
