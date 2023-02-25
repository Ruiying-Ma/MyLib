//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_BINTREE_H
#define MY_LIB_BINTREE_H

#include "binnode.h"
#include "../_share/release.h"
template <typename T> class BinTree {
protected:
    Rank _size;
    BinNodePosi<T> _root;
    virtual Rank updateHeight( BinNodePosi<T> x); // update x's height, return x's height
    void updateHeightAbove(BinNodePosi<T> x); // update x's and x's ancestors' heights
public:
    /* Constructor */
    BinTree(): _size(0), _root(NULL) {}
    /* Deconstructor */
    ~BinTree()
    {
        if (_size > 0 ) {
            remove(_root);
        }
    }
    /* Read-only api */
    Rank size() const
    { // size of the tree
        return _size;
    }
    bool empty() const
    {
        return !_root;
    }
    BinNodePosi<T> root() const
    {
        return _root;
    }
    /* Read-Write api */
    /*
    BinNodePosi<T> insert (T const& e)
    { // insert the root
    }
     */
    BinNodePosi<T> insert (T const& e, BinNodePosi<T> x)
    { // insert e into x's lc, return its position
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }
    BinNodePosi<T> insert (BinNodePosi<T> x, T const& e)
    { // insert e as x's rc, return its position
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }
    BinNodePosi<T> attach (BinTree<T>* &S, BinNodePosi<T> x)
    { // insert S as x's left subtree, return x's position
        x->lc = S->_root;
        if(x->lc){ // S may be empty
            x->lc->parent = x;
        }
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = NULL;
        S->_size = 0;
        release(S);
        S = NULL;
        return x;
    }
    BinNodePosi<T> attach (BinNodePosi<T> x, BinTree<T>* &S)
    { // insert S as x's right subtree
        x->rc = S;
        if (x->rc) {
            x->rc->parent = x;
        }
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = NULL;
        S->_size = 0;
        release(S);
        S = NULL;
        return x;
    }
    Rank remove (BinNodePosi<T> p); // remove p's subtree
    BinTree<T>* secede (BinNodePosi<T> x); // seperate x's subtree from the original tree, return x's tree

    template<typename VST> void travLevel(VST & visit)
    {
        if (_root) {
            _root->template travLevel(visit);
        }
    };
    template<typename VST> void travPre(VST & visit)
    {
        if (_root) {
            _root->template travPre(visit);
        }
    }
    template<typename VST> void travIn(VST & visit)
    {
        if (_root) {
            _root->template travIn(visit);
        }
    }
    template<typename VST> void travPost(VST & visit)
    {
        if (_root) {
            _root->template travPost(visit);
        }
    }

    bool operator< (BinTree<T> const& t)
    {
        return _root && t._root && (*_root < *t._root);
    }

    bool operator== (BinTree<T> const& t)
    {
        return _root && t._root && (*_root == *t._root);
    }
}; // BinTree

#endif //MY_LIB_BINTREE_H
