#pragma once

template <typename T> int log2_floor(T x) {
  if (x <= 0)
    return -1;
  for (int shift = 1; shift < sizeof(T) * 8; shift++)
    if ((x >> shift) == 0)
      return shift - 1;
  return sizeof(T) * 8;
}

template <typename T> T abs(T x) {
  if (x < 0)
    return -x;
  return x;
}

template <typename T> T max(T x, T y) { return x >= y ? x : y; }

template <typename T> T min(T x, T y) { return x >= y ? y : x; }

template <typename T> void swap(T &x, T &y) {
  T tmp = x;
  x = y;
  y = tmp;
}
