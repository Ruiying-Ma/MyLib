//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_SPLAY_H
#define MY_LIB_SPLAY_H
#include "../bst/bst.h"
template <typename T> class Splay :public BST<T> {
protected:
    BinNodePosi<T> splay(BinNodePosi<T> v); // splay v to the root, return v (the new root)
public:
    BinNodePosi<T>& search(const T& e); // override search, return new root
    BinNodePosi<T> insert(const T& e); // override insert, return new root
    bool remove(const T &e); // override remove
}; // Splay


#endif //MY_LIB_SPLAY_H
