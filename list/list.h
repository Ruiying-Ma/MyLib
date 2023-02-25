//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_LIST_H
#define MY_LIB_LIST_H

#include "listnode.h"
using Rank = unsigned int;

template <typename T> class List {
private:
    Rank _size;
    ListNodePosi<T> header, trailer; // both are dummy node
protected:
    void init(); // build an empty list
    Rank clear(){ // delete all nodes, return original size
        Rank old_size = _size;
        while (0 < _size) {
            remove(header->succ);
        }
        return old_size;
    }
    void copyNodes(ListNodePosi<T> p, Rank n); // copy nodes [p,p+n)
    void mergeSort(ListNodePosi<T> &p, Rank n);
    void selectionSort(ListNodePosi<T> p, Rank n);
    void insertionSort(ListNodePosi<T> p, Rank n);
    void radixSort(ListNodePosi<T> p, Rank n);

public:
    /* Constructor */
    List() {init();}
    List(List<T> const& L){  // copy L
        copyNodes(L.first(), L._size);
    }
    List(List<T> const& L, Rank r, Rank n); // copy L[r, r+n)
    List(ListNodePosi<T> p, Rank n) { // copy n nodes from p
        copyNodes(p, n);
    }
    /* Deconstructor */
    ~List(){
        clear();
        delete header;
        delete trailer;
    }
    /* Read-only api */
    Rank size() const {return _size;}
    bool empty() const {return _size <= 0;}
    ListNodePosi<T> first() const {return header->succ;}
    ListNodePosi<T> last() const {return trailer->pred;}
    ListNodePosi<T> operator[] (Rank r) const;
    ListNodePosi<T> find(T const& e, Rank n, ListNodePosi<T> p) const; // unsorted, [p-n, p)
    ListNodePosi<T> find(T const& e) const
    { // find e in the whole list
        return find(e, _size, trailer);
    }
    ListNodePosi<T> search(T const& e, Rank n, ListNodePosi<T> p) const; // sorted range, [p-n, p)
    ListNodePosi<T> search(T const& e)
    {
        return search(e, _size, trailer);
    }
    ListNodePosi<T> selectMax(ListNodePosi<T> p, Rank n) const; // select the maximum in [p, p+n) (with the highest rank)
    ListNodePosi<T> selectMax() const
    { // select the maximum in List
        return selectMax(header->succ, _size);
    }
    /* Read-Write api */
    ListNodePosi<T> insert(T const& e, ListNodePosi<T> p); // insert e as p's pred
    ListNodePosi<T> insert(ListNodePosi<T> p, T const& e); // insert e as p's succ
    ListNodePosi<T> insertAsLast(T const& e) {
        _size++;
        return trailer->insertAsPred(e);
    }
    ListNodePosi<T> insertAsFirst(T const& e) {
        _size++;
        return header->insertAsSucc(e);
    }
    T remove(ListNodePosi<T> p); // return the data of the removed node
    void sort(ListNodePosi<T> p, Rank n); // sort [p, p+n)
    void sort()
    {
        sort(header->succ, _size);
    }
    Rank deduplicate(); // unsorted, return # of deleted elements
    Rank uniquify(); // sorted
    void traverse(void (*visit) (T&));
    template <typename  VST> void traverse(VST &visit);
};

#endif //MY_LIB_LIST_H
