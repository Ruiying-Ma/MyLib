//
// Created by 马睿赢 on 2023/2/21.
//
#include "binnode.h"

template <typename T> template<typename VST>
void BinNode<T>::travIn(VST & visit) {
    switch (rand()%3) {
        case 1: travIn_I1(this, visit); break;
        case 2: travIn_I2(this, visit); break;
        default: travIn_R(this, visit); break;
    }
}

template <typename T, typename VST>
void travIn_I1(BinNodePosi<T> x, VST & visit) {
    Stack<BinNodePosi<T>> S;
    while (true) {
        /* go along the left vine */
        BinNodePosi<T> y = x;
        while (y) {
            S.push(y);
            y = y->lc;
        }
        /* inorder traverse */
        if (S.empty()) {break;}
        x = S.pop();
        visit(x->data);
        x = x->rc;
    }
}
template <typename T, typename VST>
void travIn_I2(BinNodePosi<T> x, VST & visit) {
    Stack<BinNodePosi<T>> S;
    while (true) {
        if(x) {
            S.push(x);
            x = x->lc;
        } else if (!S.empty()) {
            x = S.pop();
            visit(x->data);
            x = x->r;
        }
        else {
            break;
        }
    }
}
template <typename T, typename VST>
void travIn_R(BinNodePosi<T> x, VST & visit) {
    if (!x) {return;}
    if (x->lc) { travIn_R(x->lc, visit);}
    visit(x->data);
    if (x->rc) { travIn_R(x->rc, visit);}
    return;
}

template <typename T> template<typename VST>
void BinNode<T>::travLevel(VST & visit) {
    Queue<BinNodePosi<T>> Q;
    Q.enqueue(this);
    while (!Q.empty()) {
        for(int i=0; i<Q.size(); i++) {
            BinNodePosi<T> x = Q.dequeue();
            visit(x->data);
            if(x->lc) {Q.enqueue(x->lc);}
            if(x->rc) {Q.enqueue(x->rc);}
        }
    }
}

template<typename T> template<typename VST>
void BinNode<T>::travPre(VST & visit){
    switch (rand()%3) {
        case 1: travPre_I1(this, visit); break;
        case 2: travPre_I2(this, visit); break;
        default: travPre_R(this, visit); break;
    }
}

template<typename T, typename VST>
void travPre_I1(BinNodePosi<T> x, VST & visit){
    Stack<BinNodePosi<T>> S;
    while(true) {
        /* visit along the left vine */
        BinNodePosi<T> y = x; // use y to visit along the vine
        while (y) {
            visit(y->data);
            S.push(y->rc);
            y = y->lc;
        }
        /* traverse back along the left vine */
        if(S.empty()) {break;}
        x = S.pop();
    }
}

template<typename T, typename VST>
void travPre_I2(BinNodePosi<T> x, VST & visit){
    Stack<BinNodePosi<T>> S;
    if (x) {S.push(x);}
    while (!S.empty()) {
        x = S.pop();
        visit(x->data);
        // first push rc, then push lc
        if (HasRChild(*x)) {S.push(x->rc);}
        if (HasLChild(*x)) {S.push(x->lc);}
    }
}

template<typename T, typename VST>
void travPre_R(BinNodePosi<T> x, VST & visit){ // Recursion
    if(!x) {return;}
    visit(x->data);
    if (x->lc) {travPre_R(x->lc, visit); }
    if (x->rc) { travPre_R(x->rc, visit);}
}

template <typename T>
BinNodePosi<T> BinNode<T>::succ() {
    BinNodePosi<T> s = this;
    if (rc) {
        s = rc;
        while (HasLChild(*s)) {
            s = s->lc;
        }
    } else {
        while (IsRChild(*s)) {
            s = s->parent;
        }
        s = s->parent;
    }
    return s;
}