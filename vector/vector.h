//
// Created by 马睿赢 on 2023/2/21.
//

#ifndef MY_LIB_VECTOR_H
#define MY_LIB_VECTOR_H

#include "../_share/util.h"
#include "../pq/pq_completeheap.h"

using Rank = unsigned int;
#define DEFAULT_CAPACITY 3 // default initial capacity
template <typename T> class Vector {
protected:
    Rank _size;
    Rank _capacity;
    T* _elem;
    void copyFrom (T const* A, Rank lo, Rank hi); // copy from A[lo, hi)
    void expand (); // increase capacity
    void shrink (); // decrease capacity
    /* Sorting alg. */
    void bubbleSort (Rank lo, Rank hi);
    void selectionSort (Rank lo, Rank hi);
    void mergeSort (Rank lo, Rank hi);
    void heapSort (Rank lo, Rank hi);
    void quickSort (Rank lo, Rank hi);
    void shellSort (Rank lo, Rank hi);
    /*              */
    Rank partition (Rank lo, Rank hi); // create the pivot for quickSort()
public:
    /* Constructor */
    Vector (Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0)
    { // capacity = c, size = s, all items set to v
        _elem = new T[_capacity = c];
        for (_size =  0; _size < s; _elem[_size++] = v);
    }
    Vector (T const* A, Rank n)
    { // The first n elements of A
        copyFrom(A, 0, n);
    }
    Vector (T const* A, Rank lo, Rank hi)
    { // A[lo, hi)
        copyFrom(A, lo, hi);
    }
    Vector (Vector<T> const& V)
    { // V
        copyFrom(V._elem, 0, V._size);
    }
    Vector (Vector<T> const& V, Rank lo, Rank hi)
    { // V[lo, hi)
        copyFrom(V.elem, lo, hi);
    }
    /*             */
    /* Deconstuctor */
    ~Vector ()
    {
        delete [] _elem;
    }
    /*              */
    /* Read-only api */
    Rank size () const
    {
        return _size;
    }
    bool empty () const
    {
        return !_size;
    }
    Rank find (T const& e, Rank lo, Rank hi) const; // find e's (highest) rank in range T[lo, hi). If e doesn't exist, return lo-1
    Rank find (T const& e) const
    { // find e's rank in T
        return find (e, 0, _size);
    }
    Rank search (T const &e, Rank lo, Rank hi) const; // find e's (highest) rank in sorted range T[lo, hi). If e doesn't exist, return the proper rank for e to insert
    Rank search (T const& e) const
    { // find e's rank in sorted T
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    /*               */
    /* Read-Write api */
    T& operator[] (Rank r);
    const T& operator[] (Rank r) const; // can only be rvalue
    Vector<T> & operator= (Vector<T> const& );
    T remove (Rank r); // delete T[r], return T(r)
    Rank remove (Rank lo, Rank hi); // delete T[lo, hi), return # of deleted elements
    Rank insert (Rank r, T const& e); // insert e at T[r], return r
    Rank insert (T const& e)
    { // insert e at the end of T;
        return insert (_size, e);
    }
    void sort (Rank lo, Rank hi); // sort T[lo, hi)
    void sort ()
    { // sort T
        sort(0, _size);
    }
    void unsort (Rank lo, Rank hi); // shuffle T[lo, hi)
    void unsort ()
    { // shuffle T
        unsort(0, _size);
    }
    Rank deduplicate (); // return # of deleted elements
    Rank uniquify (); // deduplicate sorted T, return # of deleted elements
    void traverse (void (*visit) (T&)); // func pointer
    template <typename VST> void traverse (VST& visit); // func reference
    /*                */
}; // Vector
#endif //MY_LIB_VECTOR_H
