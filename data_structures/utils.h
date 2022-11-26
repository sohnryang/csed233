#pragma once

template <typename T> int log2_floor(T x) {
  if (x <= 0)
    return -1;
  for (int shift = 1; shift < sizeof(T) * 8; shift++)
    if ((x >> shift) == 0)
      return shift - 1;
  return sizeof(T) * 8;
}
