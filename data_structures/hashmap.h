#pragma once

#include <string>

#include <utils.h>  // expand: true
#include <vector.h> // expand: true

using u64 = unsigned long long;

class SipHash {
private:
  u64 v0, v1, v2, v3;
  unsigned char key[16];

  u64 bytes_to_u64(const unsigned char *bytes) {
    return (u64)bytes[0] | ((u64)bytes[1] << 8) | ((u64)bytes[2] << 16) |
           ((u64)bytes[3] << 24) | ((u64)bytes[4] << 32) |
           ((u64)bytes[5] << 40) | ((u64)bytes[6] << 48) |
           ((u64)bytes[7] << 56);
  }

  u64 left_circular_shift(u64 x, int shift) {
    return (x << shift) | (x >> (64 - shift));
  }

  void init() {
    u64 k0 = bytes_to_u64(key), k1 = bytes_to_u64(key + 8);
    v0 = k0 ^ 0x736f6d6570736575;
    v1 = k1 ^ 0x646f72616e646f6d;
    v2 = k0 ^ 0x6c7967656e657261;
    v3 = k1 ^ 0x7465646279746573;
  }

  void round() {
    v0 += v1;
    v2 += v3;
    v1 = left_circular_shift(v1, 13);
    v3 = left_circular_shift(v3, 16);
    v1 ^= v0;
    v3 ^= v2;
    v0 = left_circular_shift(v0, 32);
    v2 += v1;
    v0 += v3;
    v1 = left_circular_shift(v1, 17);
    v3 = left_circular_shift(v3, 21);
    v1 ^= v2;
    v3 ^= v0;
    v2 = left_circular_shift(v2, 32);
  }

public:
  SipHash(const char *key) {
    for (int i = 0; i < 16; i++)
      this->key[i] = key[i];
  }

  SipHash(const SipHash &other) {
    for (int i = 0; i < 16; i++)
      key[i] = other.key[i];
  }

  SipHash &operator=(const SipHash &other) {
    if (this == &other)
      return *this;
    for (int i = 0; i < 16; i++)
      key[i] = other.key[i];
    return *this;
  }

  u64 operator()(const char *data, int len) {
    init();
    unsigned char block_buf[8];
    int len_with_padding = len / 8 * 8 + 8;
    for (int i = 0; i < len_with_padding; i += 8) {
      int block_len = min_val(8, len - i);
      int j;
      for (j = 0; j < block_len; j++)
        block_buf[j] = data[i + j];
      if (block_len != 8) {
        for (; j < 8; j++)
          block_buf[j] = 0;
        block_buf[7] = len % 256;
      }
      u64 block = bytes_to_u64(block_buf);
      v3 ^= block;
      for (int j = 0; j < 2; j++)
        round();
      v0 ^= block;
    }
    v2 ^= 0xff;
    for (int i = 0; i < 4; i++)
      round();
    return v0 ^ v1 ^ v2 ^ v3;
  }

  u64 operator()(const std::string &data) {
    return (*this)(data.c_str(), data.length());
  }
};

enum class MetadataKind { kEmpty, kOccupied, kDeleted };

const u64 default_capacity = 1024;

template <typename K, typename V, typename H> class HashMap {
private:
  Vector<K> keys;
  Vector<V *> values;
  Vector<MetadataKind> metadata;
  H hasher;
  u64 capacity, occupied_count;
  const float load_factor = 0.75;

  u64 probe(u64 hash_value, u64 collision_count, u64 mod);
  void resize(u64 new_capacity);

public:
  HashMap<K, V, H>(const H &hasher);
  ~HashMap<K, V, H>();
  void insert(const K &key, V value);
  void remove(const K &key);
  int count(const K &key);
  V &operator[](const K &key);
};

template <typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(const H &hasher)
    : hasher(hasher), capacity(default_capacity), occupied_count(0),
      keys(default_capacity), values(default_capacity, nullptr),
      metadata(default_capacity, MetadataKind::kEmpty) {}

template <typename K, typename V, typename H>
HashMap<K, V, H>::~HashMap<K, V, H>() {
  for (u64 i = 0; i < capacity; i++)
    if (values[i] != nullptr)
      delete values[i];
}

template <typename K, typename V, typename H>
u64 HashMap<K, V, H>::probe(u64 hash_value, u64 collision_count, u64 mod) {
  return (hash_value +
          (collision_count * collision_count + collision_count) / 2) %
         mod;
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::resize(u64 new_capacity) {
  Vector<K> new_keys(new_capacity);
  Vector<V *> new_values(new_capacity, nullptr);
  Vector<MetadataKind> new_metadata(new_capacity, MetadataKind::kEmpty);
  K key;
  V *ptr;
  u64 hash_value, collision_count, index;
  for (int i = 0; i < capacity; i++) {
    switch (metadata[i]) {
    case MetadataKind::kEmpty:
      break;
    case MetadataKind::kOccupied:
      key = keys[i];
      ptr = values[i];
      hash_value = hasher(key);
      collision_count = -1;
      do {
        collision_count++;
        index = probe(hash_value, collision_count, new_capacity);
      } while (new_metadata[index] != MetadataKind::kEmpty);
      new_values[index] = ptr;
      new_keys[index] = key;
      new_metadata[index] = MetadataKind::kOccupied;
      break;
    case MetadataKind::kDeleted:
      key = keys[i];
      hash_value = hasher(key);
      collision_count = -1;
      do {
        collision_count++;
        index = probe(hash_value, collision_count, new_capacity);
      } while (new_metadata[index] != MetadataKind::kEmpty);
      new_keys[index] = key;
      new_metadata[index] = MetadataKind::kDeleted;
      break;
    }
  }
  metadata = new_metadata;
  keys = new_keys;
  values = new_values;
  capacity = new_capacity;
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::insert(const K &key, V value) {
  u64 hash_value = hasher(key);
  u64 collision_count = -1, index;
  do {
    collision_count++;
    index = probe(hash_value, collision_count, capacity);
  } while (metadata[index] != MetadataKind::kEmpty);
  values[index] = new V(value);
  keys[index] = key;
  metadata[index] = MetadataKind::kOccupied;
  occupied_count++;
  if (load_factor * capacity < occupied_count)
    resize(capacity * 2);
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::remove(const K &key) {
  u64 hash_value = hasher(key);
  u64 collision_count = -1, index;
  do {
    collision_count++;
    index = probe(hash_value, collision_count, capacity);
  } while (metadata[index] != MetadataKind::kOccupied || keys[index] != key);
  delete values[index];
  values[index] = nullptr;
  metadata[index] = MetadataKind::kDeleted;
}

template <typename K, typename V, typename H>
int HashMap<K, V, H>::count(const K &key) {
  u64 hash_value = hasher(key);
  u64 collision_count = -1, index;
  do {
    collision_count++;
    index = probe(hash_value, collision_count, capacity);
    if (metadata[index] == MetadataKind::kOccupied && keys[index] == key)
      return 1;
  } while (metadata[index] != MetadataKind::kEmpty);
  return 0;
}

template <typename K, typename V, typename H>
V &HashMap<K, V, H>::operator[](const K &key) {
  u64 hash_value = hasher(key);
  u64 collision_count = -1, index;
  do {
    collision_count++;
    index = probe(hash_value, collision_count, capacity);
  } while (metadata[index] != MetadataKind::kOccupied || keys[index] != key);
  V *ptr = values[index];
  return *ptr;
}
