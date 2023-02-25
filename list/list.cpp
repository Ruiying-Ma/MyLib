//
// Created by 马睿赢 on 2023/2/21.
//
#include "list.h"

template <typename T> ListNodePosi<T> List<T>::operator[](Rank r) const {
    ListNodePosi<T> p = first();
    while (0 < r--) {
        p = p->succ;
    }
    return p;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi<T> p, Rank n) {
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
Rank List<T>::deduplicate() {
    Rank old_size = _size;
    ListNodePosi<T> p = first();
    for(Rank r = 0; p != trailer; p = p->succ) { // r is the length of deduplicated prefix
        ListNodePosi<T> q = find (p->data, r, p);
        if (q) {
            remove (q);
        } else {
            r++;
        }
    }
    return old_size - _size;
}

template <typename T>
ListNodePosi<T> List<T>::find(T const& e, Rank n, ListNodePosi<T> p) const {
    assert((0 <= n) && (n <= _size));
    while (0 < n--) {
        p = p->pred;
        if (e == p->data) {
            return p;
        }
    }
    return NULL;
}

template <typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->succ = NULL; trailer->pred = header;
    _size = 0;
}

template <typename T>
ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p){
    _size++;
    return p->insertAsPred(e);
};

template <typename T>
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const& e){
    _size++;
    return p->insertAsSucc(e);
};

template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, Rank n) {
    for(Rank r = 0; r < n; r++) {
        insert(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::mergeSort(ListNodePosi<T> &p, Rank n) {
    if (n < 2) {return;}
    ListNodePosi<T> q = p;
    Rank m = n >> 1;
    for(Rank i = 0; i < m; i++) {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n-m);
    // merge
    ListNodePosi<T> pp = p->pred; // after merging, p no longer points to the first node, so we need to memorize pp
    Rank length_l = m, length_r = n-m;
    while ((0 < length_r) && (q != p)) {
        if ((0 < length_l) && (p->data <= q->data)) {
            p = p->succ;
            length_l--;
        } else {
            q = q->succ;
            insert(remove(q->pred),p);
            length_r--;
        }
    }
    p = pp->succ; // after mergesort, p should still point to the first node
}

template <typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
ListNodePosi<T> List<T>::search(const T &e, Rank n, ListNodePosi<T> p) const {
    do {p = p->pred; n--;}
    while ((-1 != n) && (e < p->data)); // either p is out of range or p->data <= e
    return p;
}

template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, Rank n) {
    ListNodePosi<T> head = p->pred, tail = p;
    for (Rank i = 0; i<n; i++) {
        tail = tail->succ;
    } // the range to be sorted is (head, tail)
    while (1 < n) {
        insert(remove(selectMax(head->succ, n)), tail); // must use 'head->succ' instead of 'p', since 'p' may change / disappear.
        tail = tail->pred;
        n--;
    }

}

template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, Rank n) const {
    ListNodePosi<T> max = p;
    for(ListNodePosi<T> cur = p->succ; 1 < n; n--) {
        if(cur->data >= max->data) {
            max = cur;
        }
        cur = cur->succ;
    }
    return max;
}

template <typename T>
void List<T>::sort(ListNodePosi<T> p, Rank n) {
    switch (rand()%3) {
        case 0 : {
            printf("insertion\n");
            insertionSort(p, n);
            break;
        }
        case 1 : {
            printf("selection\n");
            selectionSort(p, n);
            break;
        }
        case 2 : {
            printf("merge\n");
            mergeSort(p, n);
            break;
        }
            // default:radixSort(p, n); break;
    }
}

template <typename T> template <typename VST>
void List<T>::traverse(VST &visit) {
    for(ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template <typename T>
void List<T>::traverse(void (*visit) (T&)) {
    for(ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template <typename T>
Rank List<T>::uniquify() {
    Rank old_size = _size;
    ListNodePosi<T> p = first();
    ListNodePosi<T> q = p->succ;
    while (q != trailer) {
        if (p->data == q->data) {
            remove(q);
        } else {
            p = q;
        }
        q = p->succ;
    }
    return old_size - _size;
}

using U = unsigned int; // T can be forced to transfer into U
template<typename T>
void List<T>::radixSort(ListNodePosi<T> p, Rank n) {
    ListNode<T> head = p->pred;
    ListNode<T> tail = p;
    for(Rank i = 0; i<n; i++) {
        tail = tail->succ;
    }// the sorting range is (head, tail)
    for(U radixBit = 0x1; radixBit && (p = head); radixBit <<=1) { // at the beginning of each iteration, set p to head and test whether p exists
        // bucket sort
        for(Rank i = 0; i<n; i++) {
            (radixBit & U(p->succ->data)) ? insert(remove(p->succ), tail) : p = p->succ;
        }
    }
}