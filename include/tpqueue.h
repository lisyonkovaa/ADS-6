// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cassert>

struct SYM {
  char ch;
  int prior;
};

template<typename T, int size>
class TPQueue {
 private:
  T* arr;
  int sizeQueue;
  int begin, end;
  int count;

 public:
  TPQueue():sizeQueue(size), begin(0), end(0), count(0) {
    arr = new T[sizeQueue + 1];
  }

  ~TPQueue() {
    delete[] arr;
  }

  void push(const T& value) {
    assert(count < sizeQueue);

    count++;
    int b = begin, e = end;
    while (arr[b].prior >= value.prior && b != end)
    b = (b + 1) % size;
    while (e != b) {
      arr[e] = arr[(e - 1) % size];
      e = (size + e - 1) % size;
    }
    end = (end + 1) % size;
    arr[b] = value;
  }

  char get() {
    assert(count > 0);
    return arr[begin].ch;
  }

  const T& pop() {
    assert(count > 0);
    count--;
    if (begin > sizeQueue) {
      begin -= sizeQueue + 1;
    }
    return arr[begin++];
  }

  bool isEmpty() const {
    return count == 0;
  }

  bool isFull() const {
    return count == sizeQueue;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
