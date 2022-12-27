#include <cstddef>
#include <cstdint>
#include <string>

#include <hashmap.h>

int fuzz(const uint8_t *data, size_t size) {
  char key[16] = "hell world!";
  HashMap<std::string, int, SipHash> hashmap(key);
  for (size_t i = 0; i < size; i++) {
    std::string key = std::to_string(data[i]);
    if (!hashmap.count(key))
      hashmap.insert(key, 0);
    hashmap[key]++;
  }
  for (size_t i = 0; i < size; i++) {
    std::string key = std::to_string(data[i]);
    hashmap[key]--;
    if (hashmap[key] == 0)
      hashmap.remove(key);
  }
  for (size_t i = 0; i < size; i++)
    if (hashmap.count(std::to_string(data[i])))
      __builtin_trap();
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (fuzz(Data, Size))
    __builtin_trap();
  return 0;
}
