//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_BTNODE_H
#define MY_LIB_BTNODE_H
#include "../vector/vector.h"
#include "../_share/release.h"
template <typename T> struct BTNode;
template <typename T> using BTNodePosi = BTNode<T>*;

template <typename T> struct BTNode {
    BTNodePosi<T> parent;
    Vector<T> key;
    Vector<BTNodePosi<T>> child; // #child = #key + 1
    /* Constructor */
    BTNode(): parent(NULL) {child.insert(NULL);} // a node without any key
    BTNode(T e, BTNodePosi<T> lc = NULL, BTNodePosi<T> rc = NULL): parent(NULL) { // root node
        key.insert(e);
        child.insert(lc);
        child.insert(rc);
        if (lc) {lc->parent = this;}
        if (rc) {rc->parent = this;}
    }

};
#endif //MY_LIB_BTNODE_H
