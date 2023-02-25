//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_BST_H
#define MY_LIB_BST_H

#include "../bintree/bintree.h"
template <typename T> class BST : public BinTree<T> {
protected:
    BinNodePosi<T> _hot; // the parent of the 'hit' node
    BinNodePosi<T> connect34 (BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>); // connect 3 nodes and 4 subtrees to restructure the tree
    BinNodePosi<T> rotateAt (BinNodePosi<T> x); // rotate at x, x's parent and x's grandparent
    static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot);
public:
    /* with "virtual" to force all derived classes to override them */
    virtual BinNodePosi<T>& search (const T& e); // return e's node (if exists) or NULL (if doesn't exist); REMARK: return the reference
    virtual BinNodePosi<T> insert(const T& e); // return the newly inserted node's position
    virtual bool remove (const T& e); // _hot is changed to the parent of the node which is actually delete
};

#endif //MY_LIB_BST_H
