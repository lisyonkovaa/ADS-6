// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cassert>

template<typename T>
class TPQueue {
private:
    T *arr;
    int size;
    int begin, end;
    int count;

public:
    TPQueue(int = 100);
    ~TPQueue();
    
    void push(const T &);
    T pop();
    bool isEmpty() const;
    bool isFull() const;
};

template<typename T>
TPQueue<T>::TPQueue(int size) :
        size(size),
        begin(0), end(0), count(0) {
    arr = new T[size + 1];
}

template<typename T>
TPQueue<T>::~TPQueue() {
    delete[] arr;
}

template<typename T>
void TPQueue<T>::push(const T &elem) {
    assert(count < size);

    int prior = elem.prior;
    int cur = end;
    while (cur != begin && prior > arr[(cur - 1) % size].prior) {
        arr[cur] = arr[(cur - 1) % size];
        cur = (cur - 1) % size;
    }
    arr[cur] = elem;
    end = (end + 1) % size;
    count++;
}

template<typename T>
T TPQueue<T>::pop() {
    assert(count > 0);

    T elem = arr[begin];
    begin = (begin + 1) % size;
    count--;
    return elem;
}

template<typename T>
bool TPQueue<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
bool TPQueue<T>::isFull() const {
    return count == size;
}


struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
