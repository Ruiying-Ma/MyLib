//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_LISTNODE_H
#define MY_LIB_LISTNODE_H

#include "../_share/util.h"
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*;

template <typename T> struct ListNode {
    T data;
    ListNodePosi<T> pred, succ;
    /* Constrcutor */
    ListNode() {} // especially for header and trailer
    ListNode(T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL) : data (e), pred (p), succ (s) {}
    /* api */
    ListNodePosi<T> insertAsPred (T const& e) {
        ListNodePosi<T> x = new ListNode<T>(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }; // insert e immediately before the current node
    ListNodePosi<T> insertAsSucc (T const& e) {
        ListNodePosi<T> x = new ListNode<T> (e, this, succ);
        succ->pred = x;
        this->succ = x;
        return x;
    }; // insert e immediately after the current node
};


#endif //MY_LIB_LISTNODE_H
