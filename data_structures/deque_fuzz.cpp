#include <cstddef>
#include <cstdint>
#include <deque.h>

enum CommandType { PushBack, PushFront, PopBack, PopFront };

int fuzz(const uint8_t *data, size_t size) {
  Deque<int> dq;
  int elem;
  for (int i = 1; i < size; i += 2) {
    int command = data[i - 1] % 4, arg = data[i];
    switch (command) {
    case PushBack:
      dq.push_back(arg);
      break;
    case PushFront:
      dq.push_front(arg);
      break;
    case PopBack:
      if (dq.size() == 0)
        continue;
      elem = dq.pop_back();
      break;
    case PopFront:
      if (dq.size() == 0)
        continue;
      elem = dq.pop_back();
      break;
    }
  }
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  return fuzz(Data, Size);
}
