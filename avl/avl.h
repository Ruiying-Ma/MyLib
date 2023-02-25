//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_AVL_H
#define MY_LIB_AVL_H

#include "../bst/bst.h"
#include "avl_macro.h"
template <typename T> class AVL : public BST<T> {
public:
    BinNodePosi<T> insert(const T& e);
    bool remove(const T& e);
};

#endif //MY_LIB_AVL_H
