//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_BINNODE_H
#define MY_LIB_BINNODE_H

#include "../_share/util.h"
#include "../stack/stack_vector.h"
#include "../queue/queue.h"
#include "binnode_avl_macro.h"
#include "binnode_basic_macro.h"
#include "binnode_redblack_macro.h"

using Rank = unsigned int;

#if defined(MY_LIB_REDBLACK_H) // in RBTree
#define stature(p) ( (p)? (p)->height : 0 ) // outer node of an rbtree has black-height 0
#else // in other BinTree
#define stature(p) ( (int) ( (p)?(p)->height : -1 ) )
#endif

typedef enum {RB_RED, RB_BLACK} RBColor;
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*;

template <typename T > struct BinNode {
    T data;
    Rank height;
    Rank npl;
    BinNodePosi<T> parent, lc, rc;
    RBColor color;
    /* Constructor */
    BinNode(): parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
            int h = 0, int l = 1, RBColor c = RB_RED): data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
    /* api */
    Rank size()
    { // its subtree's size, implemented by preorder traverse
        Rank s = 1;
        if (lc) {
            s += lc->size();
        }
        if (rc) {
            s += rc->size();
        }
        return s;
    }
    BinNodePosi<T> insertAsLC (T const& e)
    {
        return lc = new BinNode<T>(e, this);
    };
    BinNodePosi<T> insertAsRC (T const& e)
    {
        return rc = new BinNode<T>(e, this);
    };
    BinNodePosi<T> succ(); // successor of current node (in-order traverse)
    /* traverse this node's subtree */
    template<typename VST> void travLevel(VST & visit);
    template<typename VST> void travPre(VST & visit);
    template<typename VST> void travIn(VST & visit);
    template<typename VST> void travPost(VST & visit);

    bool operator< (BinNode const& bn) {return data < bn.data;}
    bool operator== (BinNode const& bn) {return data == bn.data;}

};

#endif //MY_LIB_BINNODE_H
