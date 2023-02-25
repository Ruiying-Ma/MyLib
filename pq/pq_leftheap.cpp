//
// Created by Mary on 2023/2/24.
//
#include "pq_leftheap.h"

template <typename T>
void PQ_LeftHeap<T>::insert(T e) {
    this->_root = merge(this->_root, new BinNode<T>(e, NULL));
    this->_size++;
}

template <typename T>
T PQ_LeftHeap<T>::delMax(){
    T e = this->_root->data;
    BinNodePosi<T> lHeap = this->_root->lc;
    BinNodePosi<T> rHeap = this->_root->rc;
    if (lHeap) {lHeap->parent = NULL;}
    if (rHeap) {rHeap->parent = NULL;}
    delete this->_root;
    this->_size--;
    this->_root = merge(lHeap, rHeap);
    return e;
}

template <typename T>
BinNodePosi<T> merge_recursive(BinNodePosi<T> a, BinNodePosi<T> b) {
    // base case
    if (!a) {return b;}
    if (!b) {return a;}
    // decrease
    if (a->data < b->data) {swap(a, b);} // ensure that a's data >= b's data
    (a->rc = merge(a->rc, b))->parent = a;
    // conquer
    if (!a->lc || a->lc->npl < a->rc->npl) {
        swap(a->lc, a->rc);
    }
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    return a;
}

template <typename T>
BinNodePosi<T> merge_iterative(BinNodePosi<T> a, BinNodePosi<T> b) {
    // special case
    if (!a) {return b;}
    if (!b) {return a;}
    // ensure that a's data >= b's data
    if (a->data < b->data) {swap(a, b);}
    // iteration
    for(; a->rc; a = a->rc) {
        if (a->rc->data < b->data) {
            b->parent = a;
            swap(a->rc, b);
        }
    } // now a->rc == NULL, while b is not empty
    // connect the remaining b to a->rc
    (a->rc = b)->parent = a;
    // tilt to left
    for(; a; b = a, a = a->parent) { // b = a->rc
        if (!a->lc || a->lc->npl < a->rc->npl) {
            swap(a->lc, a->rc);
        }
        a->npl = (a->rc) ? a->rc->npl + 1 : 1;
    }
    return b;
}


template <typename T>
BinNodePosi<T> merge(BinNodePosi<T> a, BinNodePosi<T> b){
    switch (rand()%2) {
        case 0:
            return merge_iterative(a, b);
        default:
            return merge_recursive(a, b);
    }
}
