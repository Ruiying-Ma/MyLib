//
// Created by Mary on 2023/2/24.
//

#ifndef MY_LIB_PQ_LEFTHEAP_H
#define MY_LIB_PQ_LEFTHEAP_H
#include "../bintree/bintree.h"
#include "pq.h"
template <typename T> BinNodePosi<T> merge(BinNodePosi<T>, BinNodePosi<T>); // only implement the "merge" in terms of structure. The size of the tree should be updated outside the function

template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T> {
public:
    void insert(T);
    T getMax() {return this->_root->data;}
    T delMax();
    /* Constructor */
    PQ_LeftHeap(PQ_LeftHeap &A, PQ_LeftHeap &B) {
        this->_root = merge(A._root, B._root);
        this->_size = A._size + B._size;
        A._root = B._root = NULL;
        A._size = B._size = 0;
    }
};

#endif //MY_LIB_PQ_LEFTHEAP_H
