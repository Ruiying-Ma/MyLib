//
// Created by 马睿赢 on 2023/2/22.
//

#include "splay.h"

template<typename NodePosi> inline
void attachAsLC(NodePosi lc, NodePosi p) {
    // attach lc as p's lc
    p->lc = lc;
    if (lc) {lc->parent = p;}
}

template<typename NodePosi> inline
void attachAsRC(NodePosi p, NodePosi rc) {
    // attach rc as p's rc
    p->rc = rc;
    if (rc) {rc->parent = p;}
}


template <typename T>
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v) {
    if(!v) {return NULL;}
    BinNodePosi<T> p, g;
    /* 双层旋转 */
    while ((p = v->parent) &&( g = p->parent)) {
        BinNodePosi<T> gg = g->parent; // gg will be v's new parent after rotation
        // rotate
        if (IsLChild(*v)) {
            if (IsLChild(*p)) {
                attachAsLC(v->pc, p);
                attachAsLC(p->rc, g);
                attachAsRC(v, p);
                attachAsRC(p, g);
            } else {
                attachAsRC(g, v->lc);
                attachAsLC(v->rc, p);
                attachAsLC(g, v);
                attachAsRC(v, p);
            }
        } else {
            if (IsLChild(*p)) {
                attachAsRC(p, v->lc);
                attachAsLC(v->rc, g);
                attachAsRC(v, g);
                attachAsLC(p, v);
            } else {
                attachAsRC(g, p->lc);
                attachAsRC(p, v->lc);
                attachAsLC(p, v);
                attachAsLC(g, p);
            }
        }
        // attach v to gg
        if(!gg) {
            v->parent = NULL;
        } else {
            (g == gg->lc) ? attachAsLC(v, gg) : attachAsRC(gg, v);
        }
        // update height
        BinTree<T>::updateHeight(v);
        BinTree<T>::updateHeight(g);
        BinTree<T>::updateHeight(p);
    }
    /* 单层旋转 */
    if (p = v->parent) {
        if(IsLChild(*v) ) {
            attachAsLC(v->rc, p);
            attachAsRC(v, p);
        } else{
            attachAsRC(p, v->lc);
            attachAsLC(p, v);
        }
        BinTree<T>::updateHeight(p);
        BinTree<T>::updateHeight(v);
    }
    /* Now v is the root */
    v->parent = NULL;
    return v;
}

template <typename T>
BinNodePosi<T>& Splay<T>::search(const T& e) {
    BinNodePosi<T> x =BST<T>::search(e);
    this->_root = splay(x ? x : this->_hot);
    return this->_root;
}

template <typename T>
BinNodePosi<T> Splay<T>::insert(const T& e) {
    if(!this->_root) {
        this->_size = 1;
        return this->_root = new BinNode<T>(e);
    }
    // search
    BinNodePosi<T> x = Splay<T>::search(e);
    //split
    if (x->data == e) {return x;}
    else if (x->data < e) {
        x->parent = this->_root = new BinNode<T> (e, NULL, x, x->rc);
        if (x->rc) {
            x->rc->parent = this->_root;
            x->rc = NULL;
        }
    } else {
        x->parent = this->_root = new BinNode<T> (e, NULL, x->lc, x);
        if (x->lc) {
            x->lc->parent = this->_root;
            x->lc = NULL;
        }
    }

    this->_size++;
    BinTree<T>::updateHeightAbove(x);
    return this->_root;
}

template <typename T>
bool Splay<T>::remove(const T &e){
    if (!this->_root || (e != search(e)->data)) {return false;}
    BinNodePosi<T> L = this->_root->lc;
    BinNodePosi<T> R = this->_root->rc;
    release(this->_root);
    if (!R) {
        this->_root = L;
        if (L) {L->parent = NULL;}
    } else {
        this->_root = R;
        R->parent = NULL;
        Splay<T>::search(e);
        this->_root->lc = L; // new root
        if (L) {L->parent = this->_root;}
    }
    this->_size--;
    if (this->_root) {BinTree<T>::updateHeight(this->_root);}
    return true;
}