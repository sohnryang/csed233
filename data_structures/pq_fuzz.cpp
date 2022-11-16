#include <cstddef>
#include <cstdint>
#include <functional>
#include <priority_queue.h>
#include <queue>
#include <vector>

int fuzz(const uint8_t *data, size_t size) {
  size_t init_data_len = size / 2;
  std::priority_queue<uint8_t, std::vector<uint8_t>, std::greater<uint8_t>>
      pq_std;
  uint8_t init_data[init_data_len];
  for (size_t i = 0; i < init_data_len; i++) {
    pq_std.push(data[i]);
    init_data[i] = data[i];
  }
  PriorityQueue<uint8_t> pq(init_data, init_data_len);
  if (pq.size() != init_data_len)
    return 1;
  for (size_t i = 0; i < init_data_len; i++) {
    if (pq.remove() != pq_std.top())
      return 1;
    pq_std.pop();
  }
  if (!pq.empty())
    return 1;
  for (size_t i = init_data_len; i < size; i++) {
    pq_std.push(data[i]);
    pq.insert(data[i]);
  }
  for (size_t i = init_data_len; i < size; i++) {
    if (pq.remove() != pq_std.top())
      return 1;
    pq_std.pop();
  }
  if (!pq.empty())
    return 1;
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (fuzz(Data, Size))
    __builtin_trap();
  return 0;
}
