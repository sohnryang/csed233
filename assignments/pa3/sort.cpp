#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

#include <deque.h> // expand: true

sortAlg::sortAlg() {
  arr_size = 0;
  arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
  string answer;
  for (int i = 0; i < arr_size - 1; i++)
    answer += to_string(arr[i]) + " ";
  answer += to_string(arr[arr_size - 1]);
  fout << answer << endl;
}

int sortAlg::partition(ofstream &fout, int left, int right) {
  int pivot = arr[left], le_end = left;
  for (int i = left + 1; i <= right; i++) {
    if (arr[i] <= pivot) {
      le_end++;
      int tmp = arr[i];
      arr[i] = arr[le_end];
      arr[le_end] = tmp;
      if (arr[le_end] != arr[i])
        printArray(fout);
    }
  }
  int tmp = arr[le_end];
  arr[le_end] = arr[left];
  arr[left] = tmp;
  if (arr[le_end] != arr[left])
    printArray(fout);
  return le_end;
}

void sortAlg::quickSort(ofstream &fout, int left, int right) {
  Deque<int> lefts, rights;
  lefts.push_back(left);
  rights.push_back(right);
  while (!lefts.empty()) {
    int lo = lefts.pop_back(), hi = rights.pop_back();
    if (lo > hi)
      continue;
    int pivot_pos = partition(fout, lo, hi);
    lefts.push_back(pivot_pos + 1);
    rights.push_back(hi);
    lefts.push_back(lo);
    rights.push_back(pivot_pos - 1);
  }
}

void sortAlg::merge(int left, int mid, int right) {
  int idx_left = left, idx_right = mid + 1, subarr_len = right - left + 1;
  int merged[subarr_len];
  int i = 0;
  while (idx_left <= mid && idx_right <= right) {
    if (arr[idx_left] <= arr[idx_right])
      merged[i++] = arr[idx_left++];
    else
      merged[i++] = arr[idx_right++];
  }
  while (idx_left <= mid)
    merged[i++] = arr[idx_left++];
  while (idx_right <= right)
    merged[i++] = arr[idx_right++];
  for (int i = 0; i < subarr_len; i++)
    arr[left + i] = merged[i];
}

void sortAlg::mergeSort(ofstream &fout, int left, int right) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  mergeSort(fout, left, mid);
  mergeSort(fout, mid + 1, right);
  merge(left, mid, right);
  if (left < right)
    printArray(fout); // DO NOT ERASE THIS LINE
}
