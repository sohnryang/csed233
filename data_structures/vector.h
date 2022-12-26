#pragma once

template <typename T> class Vector {
private:
  int capacity, arr_len;
  T *internal_arr;

public:
  Vector<T>();
  Vector<T>(int count);
  Vector<T>(int count, T value);
  Vector<T>(const Vector<T> &other);
  ~Vector<T>();
  Vector<T> &operator=(const Vector<T> &other);
  const T &operator[](int index) const;
  void push_back(T value);
  int size() const;
  T &operator[](int index);
};

template <typename T> Vector<T>::Vector() : capacity(1), arr_len(0) {
  internal_arr = new T[capacity];
}

template <typename T>
Vector<T>::Vector(int count) : capacity(count), arr_len(count) {
  internal_arr = new T[capacity];
}

template <typename T>
Vector<T>::Vector(int count, T value) : capacity(count), arr_len(count) {
  internal_arr = new T[capacity];
  for (int i = 0; i < arr_len; i++)
    internal_arr[i] = value;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other)
    : capacity(other.capacity), arr_len(other.arr_len) {
  internal_arr = new T[capacity];
  for (int i = 0; i < arr_len; i++)
    internal_arr[i] = other.internal_arr[i];
}

template <typename T> Vector<T>::~Vector() { delete[] internal_arr; }

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
  if (this == &other)
    return *this;
  if (capacity != other.capacity) {
    delete[] internal_arr;
    capacity = other.capacity;
    internal_arr = new T[capacity];
  }
  arr_len = other.arr_len;
  for (int i = 0; i < arr_len; i++)
    internal_arr[i] = other.internal_arr[i];
  return *this;
}

template <typename T> void Vector<T>::push_back(T value) {
  if (arr_len == capacity) {
    capacity *= 2;
    T *new_arr = new T[capacity];
    for (int i = 0; i < arr_len; i++)
      new_arr[i] = internal_arr[i];
    delete[] internal_arr;
    internal_arr = new_arr;
  }
  internal_arr[arr_len++] = value;
}

template <typename T> int Vector<T>::size() const { return arr_len; }

template <typename T> T &Vector<T>::operator[](int index) {
  return internal_arr[index];
}

template <typename T> const T &Vector<T>::operator[](int index) const {
  return internal_arr[index];
}
