#include <cstddef>
#include <cstdint>
#include <double_linked_list.h>

enum CommandType {
  PushBack = 0b00,
  PushFront = 0b01,
  Index = 0b10,
  Remove = 0b11
};

int fuzz(const uint8_t *data, size_t size) {
  // iterate over data by step size of 2, first element denoting command and the
  // second specifying an argument.
  // Command is determined by the last two bits:
  // 0b00: push a node to the back
  // 0b01: push a node to the front
  // 0b10: get an element from the index
  // 0b11: remove an element from the index
  // Indexes will be calculated by taking arg modulo (size of the list).
  DoubleLinkedList<int> dl;
  int list_size = 0;
  for (int i = 1; i < size; i += 2) {
    int command = data[i - 1] & 0b11, arg = data[i];
    switch (command) {
    case PushBack: {
      auto node = new TwoWayNode<int>();
      node->data = arg;
      dl.push_back(node);
      list_size++;
      break;
    }
    case PushFront: {
      auto node = new TwoWayNode<int>();
      node->data = arg;
      dl.push_front(node);
      list_size++;
      break;
    }
    case Index: {
      if (list_size == 0)
        continue;
      arg %= list_size;
      auto node = dl.get_index(arg);
      if (node->next_ptr == nullptr && node->prev_ptr == nullptr)
        return 1;
      break;
    }
    case Remove:
      if (list_size == 0)
        continue;
      arg %= list_size;
      auto node = dl.get_index(arg);
      dl.remove(node);
      delete node;
      list_size--;
      break;
    }
  }
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  return fuzz(Data, Size);
}
