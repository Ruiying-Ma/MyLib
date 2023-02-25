//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_BTREE_H
#define MY_LIB_BTREE_H
#include "btnode.h"
template <typename T> class BTree {
protected:
    Rank _size; // total number of keys
    Rank _m; // order of the B-tree, must >= 3
    BTNodePosi<T> _root;
    BTNodePosi<T> _hot; // the last node visited when running BTree::search() (if the tree is not empty)
    void solveOverflow(BTNodePosi<T>); // overflow caused by insert: split
    void solveUnderflow(BTNodePosi<T>); // underflow caused by remove: coalesce
public:
    BTree(int m = 3): _m(m), _size(0) {
        _root = new BTNode<T>();
    } // create an empty tree
    ~BTree(){
        if (_root) {release(_root);}
    }
    int const order() {return _m;}
    int const size() {return _size;}
    BTNodePosi<T>& root() {return _root;}
    bool empty() const {return !_root;}
    BTNodePosi<T> search (const T& e);
    bool insert (const T& e);
    bool remove (const T& e);
}; // BTree

#endif //MY_LIB_BTREE_H
