//
// Created by 马睿赢 on 2023/2/21.
//
#include "bst.h"

template <typename T>
BinNodePosi<T> BST<T>::insert(const T &e) {
    BinNodePosi<T>& x = search(e);
    if(!x) {
        x = new BinNode<T> (e, _hot);
        this->_size++;
        BinTree<T>::updateHeightAbove(x);
    }
    return x;
}

template <typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi<T> &x = search(e);
    if (!x) {return false;}
    /* two cases */
    removeAt(x, _hot);
    /*           */
    this->_size--;
    BinTree<T>::updateHeightAbove(_hot);
    return true;
}

template <typename T>
static BinNodePosi<T> BST<T>::removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot) { // return the node that replace the removed node. Remark: does not update the size of the tree, need to update outside this function
    BinNodePosi<T> w = x; // The node that will be actually removed
    BinNodePosi<T> succ = NULL; // The node that will replace w
    if(!HasLChild(*x)) {succ = x = x->rc;} // assign x with x->rc automatically change hot's pointer to point to succ
    else if(!HasRChild(*x)) {succ = x = x->lc;}
    else {
        w = w->succ();
        swap(w->data, x->data); // why not directly swap the two node ? Answer: YOU CAN SEE IT IN REDBLACK::REMOVE()!
        BinNodePosi<T> u = w->parent;
        ((u==x) ? u->rc : u->lc) = succ = w->rc; // special case: when u==x, we need to change u->rc instead of u->lc
    }
    hot = w->parent;
    if (succ) {
        succ->parent = hot;
    }
    release(w->data);
    release(w);
    return succ;
}

template <typename T>
BinNodePosi<T>& BST<T>::search(const T &e) {
    if (!this->_root || this->_root->data == e) {_hot = NULL; return this->_root;}
    for (_hot = this->_root; ; ) {
        BinNodePosi<T> &v = (e < _hot->data) ? _hot->lc : _hot->rc;
        if(!v || v->data == e) {return v;}
        _hot = v;
    }
}

template <typename T> BinNodePosi<T> BST<T>::connect34 (BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
        BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3
        ) {
    a->lc = T0; if ( T0 ) T0->parent = a;
    a->rc = T1; if ( T1 ) T1->parent = a; updateHeight ( a );
    c->lc = T2; if ( T2 ) T2->parent = c;
    c->rc = T3; if ( T3 ) T3->parent = c; updateHeight ( c );
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b; updateHeight ( b );
    return b; //该子树新的根节点
}

template <typename T> BinNodePosi<T> BST<T>::rotateAt( BinNodePosi<T> v ) { //v为非空孙辈节点

    BinNodePosi<T> p = v->parent; BinNodePosi<T> g = p->parent; //视v、p和g相对位置分四种情况
    if ( IsLChild( *p ) ) // zig
       if ( IsLChild( *v ) ) { /* zig-zig */
          p->parent = g->parent; //向上联接
          return connect34( v, p, g, v->lc, v->rc, p->rc, g->rc );
       } else { /* zig-zag */
          v->parent = g->parent; //向上联接
          return connect34( p, v, g, p->lc, v->lc, v->rc, g->rc );
       }
    else // zag
       if ( IsRChild( *v ) ) { /* zag-zag */
          p->parent = g->parent; //向上联接
          return connect34( g, p, v, g->lc, p->lc, v->lc, v->rc );
       } else { /* zag-zig */
          v->parent = g->parent; //向上联接
          return connect34( g, v, p, g->lc, v->lc, v->rc, p->rc );
       }
 }