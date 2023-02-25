//
// Created by 马睿赢 on 2023/2/21.
//
#include "bintree.h"
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x) {
    FromParentTo(*x) = NULL; // nullify the pointer from x's parent
    updateHeightAbove(x->parent);
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}
template <typename T>
Rank BinTree<T>::updateHeight(BinNodePosi<T> x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}