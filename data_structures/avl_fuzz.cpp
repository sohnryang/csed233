#include <avl.h>
#include <cstddef>
#include <cstdint>

int fuzz(const uint8_t *data, size_t size) {
  AVLTree<uint8_t, int> tree;
  for (size_t i = 0; i < size; i++) {
    auto node = tree.get(data[i]);
    if (node == nullptr) {
      tree.insert(data[i], 0);
      node = tree.get(data[i]);
    }
    node->value++;
  }
  for (size_t i = 0; i < size; i++) {
    auto node = tree.get(data[i]);
    node->value--;
    if (node->value == 0)
      tree.remove(data[i]);
  }
  if (tree.get_root() != nullptr)
    return 1;
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (fuzz(Data, Size))
    __builtin_trap();
  return 0;
}
