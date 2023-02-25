//
// Created by 马睿赢 on 2023/2/24.
//

#ifndef MY_LIB_PQ_COMPLETEHEAP_H
#define MY_LIB_PQ_COMPLETEHEAP_H
#include "pq.h"
#include "../vector/vector.h"
#include "pq_completeheap_macro.h"

template <typename T> struct PQ_ComplHeap : public PQ<T>, public Vector<T> {
    PQ_ComplHeap(){}
    PQ_ComplHeap(T* A, Rank n) {
        Vector<T>::copyFrom(A, 0, n);
        heapify(A, n);
    }

    void insert(T);
    T getMax();
    T delMax(); // return the original root (original max)

}; // PQ_ComplHeap

template <typename T> void heapify(T* A, Rank n);
template <typename T> Rank percolateDown(T* A, Rank n, Rank i); // return the final position of A[i]
template <typename T> Rank percolateUp(T* A, Rank i); // return the final position of A[i]
#endif //MY_LIB_PQ_COMPLETEHEAP_H
