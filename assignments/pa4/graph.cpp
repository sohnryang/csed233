#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

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
    Vector<Edge> vec;
    graph.push_back(vec);
  }
  return id;
}

Graph::LabelComparator::LabelComparator(const Graph &parent) : parent(parent) {}

int Graph::LabelComparator::operator()(const Edge &edge1,
                                       const Edge &edge2) const {
  return parent.labels[edge1.dest].compare(parent.labels[edge2.dest]);
}

Graph::WeightComparator::WeightComparator(const Graph &parent)
    : parent(parent) {}

int Graph::WeightComparator::operator()(const Edge &edge1,
                                        const Edge &edge2) const {
  if (edge1.weight != edge2.weight)
    return edge1.weight - edge2.weight;
  if (edge1.src != edge2.src)
    return parent.labels[edge1.src].compare(parent.labels[edge2.src]);
  return parent.labels[edge1.dest].compare(parent.labels[edge2.dest]);
}

template <typename T>
void Graph::mergeArr(Vector<Edge> &arr, const T &comparator, int lo, int mid,
                     int hi) {
  Vector<Edge> left_arr(mid - lo), right_arr(hi - mid);
  for (int i = 0; i < mid - lo; i++)
    left_arr[i] = arr[lo + i];
  for (int i = 0; i < hi - mid; i++)
    right_arr[i] = arr[mid + i];
  int left_idx = 0, right_idx = 0, arr_idx = lo;
  while (left_idx < mid - lo && right_idx < hi - mid) {
    if (comparator(left_arr[left_idx], right_arr[right_idx]) < 0)
      arr[arr_idx++] = left_arr[left_idx++];
    else
      arr[arr_idx++] = right_arr[right_idx++];
  }
  while (left_idx < mid - lo)
    arr[arr_idx++] = left_arr[left_idx++];
  while (right_idx < hi - mid)
    arr[arr_idx++] = right_arr[right_idx++];
}

template <typename T>
void Graph::sortEdges(Vector<Edge> &arr, const T &comparator) {
  for (int subarr_size = 1; subarr_size < arr.size(); subarr_size *= 2) {
    for (int lo = 0; lo < arr.size(); lo += 2 * subarr_size) {
      int mid = std::min(lo + subarr_size, (int)arr.size()),
          hi = std::min(mid + subarr_size, (int)arr.size());
      mergeArr(arr, comparator, lo, mid, hi);
    }
  }
}

void Graph::dfsTraverse(int here_id, Vector<bool> &visited,
                        Vector<int> &visit_seq) {
  visited[here_id] = true;
  visit_seq.push_back(here_id);
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].dest;
    if (!visited[there_id])
      dfsTraverse(there_id, visited, visit_seq);
  }
}

void Graph::sortGraph() { sortGraph(graph); }

void Graph::sortGraph(Vector<Vector<Edge>> &graph) {
  for (int i = 0; i < label_count; i++)
    sortEdges(graph[i], LabelComparator(*this));
}

void Graph::countCycles(int here_id, int parent_id, Vector<int> &parent,
                        Vector<int> &visited, int &count) {
  visited[here_id] = 1;
  parent[here_id] = parent_id;
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].dest;
    if (parent[here_id] == there_id)
      continue;
    if (visited[there_id] == 2)
      continue;
    if (visited[there_id] == 1) {
      count++;
      continue;
    }
    countCycles(there_id, here_id, parent, visited, count);
  }
  visited[here_id] = 2;
}

bool Graph::checkDag(int here_id, Vector<int> &visited) {
  visited[here_id] = 1;
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].dest;
    if (visited[there_id] == 2)
      continue;
    if (visited[there_id] == 1)
      return false;
    if (!checkDag(there_id, visited))
      return false;
  }
  visited[here_id] = 2;
  return true;
}

void Graph::topologicalSort(int here_id, Vector<bool> &visited,
                            Deque<int> &sort_result) {
  visited[here_id] = true;
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].dest;
    if (!visited[there_id])
      topologicalSort(there_id, visited, sort_result);
  }
  sort_result.push_front(here_id);
}

void Graph::addAdjacent(int here_id, PriorityQueue<Edge> &pq,
                        Vector<bool> &added) {
  added[here_id] = true;
  for (int i = 0; i < graph[here_id].size(); i++) {
    int there_id = graph[here_id][i].dest;
    if (!added[there_id]) {
      Edge edge = graph[here_id][i];
      edge.src = here_id;
      pq.insert(edge);
    }
  }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string Graph::DFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Vector<Edge> nodes(label_count);
  for (int i = 0; i < label_count; i++)
    nodes[i] = Edge(0, i);
  sortEdges(nodes, LabelComparator(*this));
  sortGraph();
  Vector<bool> visited(label_count, false);
  Vector<int> visit_seq;
  string result;
  for (int i = 0; i < label_count; i++) {
    int here_id = nodes[i].dest;
    if (visited[here_id])
      continue;
    if (!result.empty())
      result += "\n";
    dfsTraverse(here_id, visited, visit_seq);
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
  Vector<Edge> nodes(label_count);
  for (int i = 0; i < label_count; i++)
    nodes[i] = Edge(0, i);
  sortEdges(nodes, LabelComparator(*this));
  sortGraph();
  Vector<bool> visited(label_count, false);
  string result;
  for (int i = 0; i < label_count; i++) {
    int start_id = nodes[i].dest;
    if (visited[start_id])
      continue;
    Deque<int> queue;
    queue.push_back(start_id);
    visited[start_id] = true;
    string line = labels[start_id];
    while (!queue.empty()) {
      int here_id = queue.pop_front();
      for (int j = 0; j < graph[here_id].size(); j++) {
        int there_id = graph[here_id][j].dest;
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
    if (graph[nodeA_id][i].dest != nodeB_id)
      continue;
    graph[nodeA_id][i].weight = min_val(weight, graph[nodeA_id][i].weight);
    return 0;
  }
  graph[nodeA_id].push_back(Edge(weight, nodeB_id, nodeB));
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
  Vector<int> visited(label_count, 0), parent(label_count, -1);
  int count = 0;
  for (int i = 0; i < label_count; i++) {
    if (visited[i] == 2)
      continue;
    countCycles(i, -1, parent, visited, count);
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
  {
    Vector<int> visited(label_count, 0);
    if (!checkDag(0, visited))
      return "error";
  }
  sortGraph();
  Vector<Edge> nodes(label_count);
  for (int i = 0; i < label_count; i++)
    nodes[i] = Edge(0, i);
  sortEdges(nodes, LabelComparator(*this));
  Vector<bool> visited(label_count, false);
  Deque<int> sort_result;
  for (int i = label_count - 1; i >= 0; i--) {
    int start_id = nodes[i].dest;
    if (visited[start_id])
      continue;
    topologicalSort(start_id, visited, sort_result);
  }
  string res;
  while (!sort_result.empty()) {
    if (!res.empty())
      res += " ";
    res += labels[sort_result.pop_front()];
  }
  return res;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countDirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Vector<int> visited(label_count, 0), parent(label_count, -1);
  int count = 0;
  for (int i = 0; i < label_count; i++) {
    if (visited[i] == 2)
      continue;
    countCycles(i, -1, parent, visited, count);
    for (int j = 0; j < label_count; j++)
      if (visited[j] == 1)
        visited[j] = 2;
  }
  return count;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getShortestPath(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  sortGraph();
  Vector<int> dist(label_count, -1);
  Vector<int> parent(label_count, -1);
  int source_id = label_id_table[source];
  dist[source_id] = 0;
  PriorityQueue<Edge> pq;
  pq.insert(Edge(0, source_id, source));
  while (!pq.empty()) {
    Edge edge = pq.remove();
    int here_id = edge.dest;
    int here_dist = edge.weight;
    if (dist[here_id] >= 0 && dist[here_id] < edge.weight)
      continue;
    for (int i = 0; i < graph[here_id].size(); i++) {
      int there_id = graph[here_id][i].dest;
      int there_dist = here_dist + graph[here_id][i].weight;
      if (dist[there_id] == -1 || dist[there_id] > there_dist) {
        dist[there_id] = there_dist;
        parent[there_id] = here_id;
        pq.insert(Edge(there_dist, there_id, labels[there_id]));
      }
    }
  }
  int dest_id = label_id_table[destination];
  if (dist[dest_id] == -1)
    return "error";
  Deque<int> path;
  int current = dest_id;
  while (current != -1) {
    path.push_front(current);
    current = parent[current];
  }
  string res;
  while (!path.empty()) {
    res += labels[path.pop_front()];
    res += " ";
  }
  res += to_string(dist[dest_id]);
  return res;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string Graph::getAllShortestPaths() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Vector<Vector<Edge>> dist(label_count);
  Vector<Edge> nodes(label_count);
  for (int i = 0; i < label_count; i++)
    nodes[i] = Edge(0, i);
  sortEdges(nodes, LabelComparator(*this));
  Vector<int> node_id_inv(label_count);
  for (int i = 0; i < label_count; i++)
    node_id_inv[nodes[i].dest] = i;
  for (int i = 0; i < label_count; i++) {
    int here_id = nodes[i].dest;
    dist[i].assign(label_count, Edge(false, -1, ""));
    for (int j = 0; j < graph[here_id].size(); j++) {
      int there_id = graph[here_id][j].dest;
      dist[i][node_id_inv[there_id]].dest = there_id;
    }
    for (int j = 0; j < graph[here_id].size(); j++) {
      int there_id = graph[here_id][j].dest;
      dist[i][node_id_inv[there_id]] = graph[here_id][j];
    }
  }
  for (int i = 0; i < label_count; i++) {
    dist[i][i].weight = 0;
    dist[i][i].finite = true;
  }
  for (int k = 0; k < label_count; k++)
    for (int i = 0; i < label_count; i++)
      for (int j = 0; j < label_count; j++) {
        Edge new_dist = dist[i][k] + dist[k][j];
        dist[i][j] = min_val(dist[i][j], new_dist);
      }
  string res;
  for (int i = 0; i < label_count; i++) {
    if (!res.empty())
      res += "\n";
    string line;
    for (int j = 0; j < label_count; j++) {
      if (!line.empty())
        line += " ";
      if (!dist[i][j].finite)
        line += "INF";
      else
        line += to_string(dist[i][j].weight);
    }
    res += line;
  }
  return res;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Vector<bool> added(label_count, false);
  Vector<Edge> tree_edges;
  PriorityQueue<Edge> pq;
  int start_id = label_id_table[startNode];
  addAdjacent(start_id, pq, added);
  while (!pq.empty()) {
    Edge min_edge = pq.remove();
    int there_id = min_edge.dest;
    if (added[there_id])
      continue;
    tree_edges.push_back(min_edge);
    addAdjacent(there_id, pq, added);
  }
  for (int i = 0; i < tree_edges.size(); i++) {
    Edge edge = tree_edges[i];
    fout << labels[edge.src] << " " << labels[edge.dest] << " " << edge.weight
         << "\n";
  }
  int mst_cost = 0;
  for (int i = 0; i < tree_edges.size(); i++)
    mst_cost += tree_edges[i].weight;
  return mst_cost;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Vector<Edge> edges;
  for (int i = 0; i < graph.size(); i++) {
    for (int j = 0; j < graph[i].size(); j++) {
      Edge edge = graph[i][j];
      edge.src = i;
      edges.push_back(edge);
    }
  }
  sortEdges(edges, WeightComparator(*this));
  UnionFind uf(label_count);
  int mst_cost = 0;
  for (int i = 0; i < edges.size(); i++) {
    Edge edge = edges[i];
    if (uf.is_same_set(edge.src, edge.dest))
      continue;
    uf.union_set(edge.src, edge.dest);
    fout << labels[edge.src] << " " << labels[edge.dest] << " " << edge.weight
         << "\n";
    mst_cost += edge.weight;
  }
  return mst_cost;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
