//
// Created by 马睿赢 on 2023/2/23.
//
#include "redblack.h"

/******************************************************************************************
 * RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
 *    RR-1 (u == BLACK || u == NULL)：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    RR-2 (u == RED)：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
 ******************************************************************************************/
template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi<T> x) { // x and p are red
    if (IsRoot(*x)) {
        this->_root->color = RB_BLACK;
        this->_root->height++;
        return;
    }
    BinNodePosi<T> p = x->parent;
    if (IsBlack(p)) {return;}
    BinNodePosi<T> g = p->parent; // if p is red, g must be black
    BinNodePosi<T> u = uncle(x);
    if (IsBlack(u)) { // u is black or u is null, RR-1
        // color
        g->color = RB_RED;
        if (IsLChild(*x) == IsLChild(*p)) { // g, p, x form a simple list
            p->color = RB_BLACK;
        } else {
            x->color = RB_RED;
        }
        // rotate
        BinNodePosi<T> gg = g->parent;
        BinNodePosi<T> r = ( IsRoot(*g) ? this->_root : ( IsLChild(*g) ? g->parent->lc : g->parent->rc ) ) = BST<T>::rotateAt(x);
        r->parent = gg;
    } else { // u is red, RR-2
        p->color = RB_BLACK;
        p->height++;
        u->color = RB_BLACK;
        u->height++;
        g->color = RB_RED;
        solveDoubleRed(g);
    }

}


/******************************************************************************************
 * RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
 * 分为三大类共四种情况：
 *    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
 *    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
 *    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
 ******************************************************************************************/
template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi<T> r) {
    BinNodePosi<T> p = r ? r->parent : this->_hot;
    if (!p) {return;}
    BinNodePosi<T> s = (r == p->lc) ? p->rc : p->lc;
    if (IsBlack(s)) {
        BinNodePosi<T> t = NULL; // t is the red child of s if exists
        if (IsRed(s->rc)) {t = s->rc;}
        if (IsRed(s->lc)) {t = s->lc;}
        if (t) { // BB-1 case
            RBColor OldColor = p->color;
            BinNodePosi<T> b = ((!((*p).parent)) ? this->_root : ((!(!((*p).parent)) && (&(*p) == (*p).parent->lc)) ? (*p).parent->lc : (*p).parent->rc)) = BST<T>::rotateAt(t);
            if (HasLChild(*b)) {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            }
            if (HasRChild(*b)) {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = OldColor;
            updateHeight(b);
        } else { //BB-2 case
            s->color = RB_RED;
            s->height--;
            if (IsRed(p)) { //BB-2R case
                p->color = RB_BLACK;
            } else {
                p->height--;
                solveDoubleBlack(p);
            }
        }
    } else { // BB-3 case
        s->color = RB_BLACK;
        p->color = RB_RED;
        BinNodePosi<T> t = IsLChild(*s) ? s->lc : s->rc;
        this->_hot = p;
        ((!((*p).parent)) ? this->_root : ((!(!((*p).parent)) && (&(*p) == (*p).parent->lc)) ? (*p).parent->lc : (*p).parent->rc)) = BST<T>::rotateAt(t);
        solveDoubleBlack(r);
    }
}

template <typename T>
BinNodePosi<T> RedBlack<T>::insert(const T& e) {
    BinNodePosi<T> x = BST<T>::search(e);
    if (x) {return x;}
    x = new BinNode<T>(e, this->_hot, NULL, NULL, 0); // the last '0' is to set the height of x, and x's color is set to RED by default
    BinNodePosi<T> xOld = x; // xOld is used to remember x
    solveDoubleRed(x);
    return xOld;
    //TODO: to be answered: why we need to save xOld ? It seems that x's data has not change...
}

template <typename T>
bool RedBlack<T>::remove(const T& e) {
    BinNodePosi<T>& x = BST<T>::search(e);

    if (!x) {return false;}

    BinNodePosi<T> r = BST<T>::removeAt(x, this->_hot);

    if (!(--this->_size)) {return true;} // after removing x, the tree becomes empty

    if (!this->_hot) { // if the removed node x is originally the root
        this->_root->color =  RB_BLACK;
        updateHeight(this->_root);
        return true;
    }

    if (BlackHeightUpdated(*this->_hot)) {return true;} // if after the remove, the tree is still a RBTree

    // if originally, at least one of x and r is red
        // if both red, no need to change
        // if x is red, no need to change
        // if r is red (x is black), simply change r to black and update height
        if (IsRed(r)) {
            r->color = RB_BLACK;
            r->height++;
            return true;
        }

    // now we must consider the "double black" condition
    solveDoubleBlack(r);
    return true;
}