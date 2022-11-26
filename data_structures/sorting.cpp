#include "sorting.h"

#include <deque.h>

int partition(int *arr, int left, int right) {
  int pivot = arr[left], le_end = left;
  for (int i = left + 1; i <= right; i++) {
    if (arr[i] <= pivot) {
      le_end++;
      int tmp = arr[i];
      arr[i] = arr[le_end];
      arr[le_end] = tmp;
    }
  }
  int tmp = arr[le_end];
  arr[le_end] = arr[left];
  arr[left] = tmp;
  return le_end;
}

void quick_sort(int *arr, int left, int right) {
  Deque<int> lefts, rights;
  lefts.push_back(left);
  rights.push_back(right);
  while (!lefts.empty()) {
    int lo = lefts.pop_back(), hi = rights.pop_back();
    if (lo > hi)
      continue;
    int pivot_pos = partition(arr, lo, hi);
    lefts.push_back(lo);
    rights.push_back(pivot_pos - 1);
    lefts.push_back(pivot_pos + 1);
    rights.push_back(hi);
  }
}

void merge_arr(int *arr, int left, int mid, int right) {
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

void merge_sort(int *arr, int left, int right) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);
  merge_arr(arr, left, mid, right);
}
