//
// Created by 马睿赢 on 2023/2/24.
//

#include "pq_completeheap.h"
template <typename T>
void heapify(T* A, Rank n) { // Floyd: From bottom to top, percolate down
    for(Rank i = n/2 - 1; i != -1; i--) {
        percolateDown(A, n, i);
    }
}

template <typename T>
Rank percolateUp(T* A, Rank i) {
    while (i > 0) {
        Rank j = Parent(i);
        if (A[i] <= A[j]) {break;}
        swap(A[i], A[j]);
        i = j;
    }
    return i;
}

template <typename T>
Rank percolateDown(T* A, Rank n, Rank i) {
    Rank j;
    while(i != (j = ProperParent(A, n, i))) {
        swap(A[i], A[j]);
        i = j;
    }
    return i;
}

template <typename T>
void PQ_ComplHeap<T>::insert(T e) {
    Vector<T>::insert(e);
    percolateUp(this->_elem, this->_size-1);
}

template <typename T>
T PQ_ComplHeap<T>::getMax() {
    return this->_elem[0];
}

template <typename T>
T PQ_ComplHeap<T>::delMax() {
    swap(this->_elem[0], this->_elem[--this->_size]);
    percolateDown(this->_elem, this->_size, 0);
    return this->_elem[this->_size]; 
}
