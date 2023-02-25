//
// Created by 马睿赢 on 2023/2/23.
//

#ifndef MY_LIB_REDBLACK_H
#define MY_LIB_REDBLACK_H

#include "../bst/bst.h"

template <typename T> class RedBlack : public BST<T> {
protected:
    void solveDoubleRed(BinNodePosi<T> x); // "double red" means: after insertion, x and x's parent are both red
    void solveDoubleBlack(BinNodePosi<T> x); // "double black" means: the deleted node x and the replacing node r are both black ( r is x's rc )
    Rank updateHeight(BinNodePosi<T> x){ // in RedBlack tree, height of a node refers to its black height
        return x->height = IsBlack(x) + max(stature(x->lc), stature(x->rc));
    };
public:
    BinNodePosi<T> insert(const T& e);
    bool remove(const T& e);
    // BST<T>::search() and other api's can be directly inherited

};
#endif //MY_LIB_REDBLACK_H
