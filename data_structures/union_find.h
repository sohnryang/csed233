#pragma once

class UnionFind {
private:
  int *parent, *rank, *set_size;
  int set_count;

public:
  UnionFind(int element_count) {
    set_size = new int[element_count];
    for (int i = 0; i < element_count; i++)
      set_size[i] = 1;
    set_count = element_count;
    rank = new int[element_count]();
    parent = new int[element_count]();
    for (int i = 0; i < element_count; i++)
      parent[i] = i;
  }

  ~UnionFind() {
    delete[] parent;
    delete[] rank;
    delete[] set_size;
  }

  int find_set(int i) {
    return (parent[i] == i) ? i : (parent[i] = find_set(parent[i]));
  }

  bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }

  void union_set(int i, int j) {
    if (!is_same_set(i, j)) {
      set_count--;
      int x = find_set(i), y = find_set(j);
      if (rank[x] > rank[y]) {
        parent[y] = x;
        set_size[x] += set_size[y];
      } else {
        parent[x] = y;
        set_size[y] += set_size[x];
        if (rank[x] == rank[y])
          rank[y]++;
      }
    }
  }
};
