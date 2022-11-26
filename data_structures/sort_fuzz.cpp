#include <cstddef>
#include <cstdint>
#include <sorting.h>

int fuzz(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;
  int arr[size];
  for (int i = 0; i < size; i++)
    arr[i] = data[i];
  if (size % 2 == 0) {
    int pivot = data[0];
    int pivot_pos = partition(arr, 0, size - 1);
    if (pivot != arr[pivot_pos])
      return 1;
    for (int i = 0; i < size; i++) {
      if (i <= pivot_pos && arr[i] > pivot)
        return 1;
      if (i > pivot_pos && arr[i] <= pivot)
        return 1;
    }
    return 0;
  }
  quick_sort(arr, 0, size - 1);
  for (int i = 1; i < size; i++)
    if (arr[i - 1] > arr[i])
      return 1;
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (fuzz(Data, Size))
    __builtin_trap();
  return 0;
}
