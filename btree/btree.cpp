//
// Created by 马睿赢 on 2023/2/22.
//

#include "btree.h"

template <typename T>
BTNodePosi<T> BTree<T>::search (const T& e){
    BTNodePosi<T> v = _root;
    _hot = NULL;
    while(v) {
        Rank r = v->key.search(e); // key[r] is the largest key that <= e. Remark: if key vector is empty, "search" returns -1
        if ( r>= 0 && v->key[r] == e) {return v;}
        _hot = v;
        v = v->child[r+1];
    }
    return NULL; // v touches the outer node
}

template <typename T>
bool BTree<T>::insert (const T& e){
    BTNodePosi<T> v = BTree<T>::search(e);
    if (v) {return false;}
    Rank r = _hot->key.search(e);
    _hot->key.insert(r+1, e);
    _hot->child.insert(r+2, NULL);
    _size++;
    BTree<T>::solveOverflow(_hot);
    return true;
}


template <typename T>
bool BTree<T>::remove (const T& e){
    BTNodePosi<T> v = BTree<T>::search(e);
    if (!v) {return false;}
    // ensure that the target is in the leaf node by finding its succ and swaping
    Rank r = v->key.search(e);
    if (v->child[0]) { // if v is not a leaf
        BTNodePosi<T> u = v->child[r+1]; // u is e's rc
        while(u->child[0]) {
            u = u->child[0];
        } // now u is the leaf where e's succ is in
        v->key[r] = u->key[0]; // swap
        v = u;
        r = 0;
    } // now we need to delete v->key[r] and v must be a leaf
    v->key.remove(r);
    v->child.remove(r+1);
    _size--;
    solveUnderflow(v);
    return true;


}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi<T> v) {
    while (_m <= v->key.size()) {
        Rank s = _m>>1;
        BTNodePosi<T> u = new BTNode<T>(); // u is the new rc after split, v is saved to be lc after split
        for(Rank j = 0; j<_m-s-1; j++) {
            u->child.insert(j, v->child.remove(s+1));
            u->key.insert(j, v->key.remove(s+1));
        }
        u->child[_m-s-1] = v->child.remove(s+1); // remember the last child of u (#child = #key + 1)
        if (u->child[0]) { // let all u's children point to u
            for(Rank j = 0; j<_m-s; j++) {
                u->child[j]->parent = u;
            }
        }
        BTNodePosi<T> p = v->parent;
        if (!p) { // if v is the root
            p = _root = new BTNode<T>();
            p->child[0] = v;
            v->parent = p;
        }
        Rank r = p->key.search(v->key[0]) + 1; // s shounld be insered in p->key[r]
        p->key.insert(r, v->key.remove(s));
        p->child.insert(r+1, u);
        u->parent = p;
        v = p;
    }
}

template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi<T> v) {
    while ((_m+1)/2 > v->child.size()) {

        BTNodePosi<T> p = v->parent;

        if (!p) { // v is the root
            if (!v->key.size() && v->child[0]) { // v has no key but has a child: after underflow, the root becomes empty, need to decrease the height of the whole tree
                _root = v->child[0];
                _root->parent = NULL;
                v->child[0] = NULL;
            }
            // else root is the only node of the tree, simply remove e
            return;
        }
        //find the rank of v in p->child: we don't use p->key.search(v->key[0]) since v may be empty
        Rank r = 0;
        while (p->child[r] != v) {
            r++;
        } // if we have implemented the operator '==' for BTNodePosi, we can use vector::find()
        // case1: v borrow key from ls
        if (r > 0) { // ls exists
            BTNodePosi<T> ls = p->child[r-1];
            if (ls->child.size() > ((_m+1)/2)) { // if ls->key.size() >= (m+1)/2
                v->key.insert(0, p->key[r-1]);
                p->key[r-1] = ls->key.remove(ls->key.size()-1);
                v->child.insert(0, ls->child.remove(ls->child.size()-1));
                if (v->child[0]) {
                    v->child[0]->parent = v;
                }
                return;
            }
        }
        // case 2: v borrow key from rs
        if (p->child.size()-1 > r) { // if rs exists
            BTNodePosi<T> rs = p->child[r+1];
            if (rs->child.size() >((_m+1)/2)) {
                v->key.insert(v->key.size(), p->key[r]);
                p->key[r] = rs->key.remove(0);
                v->child.insert(v->child.size(), rs->child.remove(0));
                if (v->child[v->child.size()-1]) {
                    v->child[v->child.size()-1]->parent = v;
                }
                return;
            }
        }
        // case 3: v coalesce with ls or rs
        if (r > 0) { // coalesce with ls
            BTNodePosi<T> ls = p->child[r-1];
            ls->key.insert(ls->key.size(), p->key.remove(r-1));
            p->child.remove(r);
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size()-1]) {
                ls->child[ls->child.size()-1]->parent = ls;
            }
            while(!v->key.empty()) {
                ls->key.insert(ls->key.size(), v->key.remove(0));
                ls->child.insert(ls->child.size(), v->child.remove(0));
                if(ls->child[ls->child.size()-1]) {
                    ls->child[ls->child.size()-1]->parent = ls;
                }
                release(v);
            }
        } else { // coalesce with rs
            BTNodePosi<T> rs = p->child[r+1];
            rs->key.insert(0, p->key.remove(r));
            p->child.remove(r);
            rs->child.insert(0, v->child.remove(v->child.size()-1));
            if (rs->child[0]) {
                rs->child[0]->parent = rs;
            }
            while(!v->key.empty()) {
                rs->key.insert(0, v->key.remove(v->key.size()-1));
                rs->child.insert(0, v->child.remove(v->child.size()-1));
                if (rs->child[0]) {
                    rs->child[0]->parent = rs;
                }
            }
            release(v);
        }
        v = p;
    } // while
}