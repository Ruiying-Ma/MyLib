//
// Created by 马睿赢 on 2023/2/21.
//
#include "avl.h"

template <typename T> BinNodePosi<T> AVL<T>::insert( const T& e ) {
    BinNodePosi<T> &x = BST<T>::search(e);
    if (x) {return x;}
    BinNodePosi<T> xx = x = new BinNode<T>(e, this->_hot);
    this->_size++;
    for(BinNodePosi<T> g = this->_hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {
            ( IsRoot(*g) ? this->_root : ( IsLChild(*g) ? g->parent->lc : g->parent->rc ) ) =
                    rotateAt(tallerChild(tallerChild(g)));
            break;
        } else {
            updateHeight(g);
        }
    }
    return xx;
}

template <typename T> bool AVL<T>::remove( const T& e ) {
    BinNodePosi<T> &x = BST<T>::search(e);
    if (!x) {return false;}
    removeAt(x, this->_hot);
    this->_size--;
    for(BinNodePosi<T> g = this->_hot; g; g = g->parent) {
        if(!AvlBalanced(*g)) {
            g = ( IsRoot(*g) ? this->_root : ( IsLChild(*g) ? g->parent->lc : g->parent->rc ) )  = rotateAt(tallerChild(tallerChild(g)));
        }
        updateHeight(g);
    }
    return true;
}