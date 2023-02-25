//
// Created by 马睿赢 on 2023/2/21.
//

#include "vector.h"
template <typename T> T& Vector<T>::operator[] (Rank r) { // can be used as lvalue
    assert((r<_size) && (r >= 0));
    return _elem[r];
}

template <typename T> const T& Vector<T>::operator[](Rank r) const { // can only be used as rvalue
    assert((r<_size) && (r >= 0));
    return _elem[r];
}

template <typename T>
void swap (T &a, T &b) {
    T t = a;
    a = b;
    b = t;
}
/* original version */
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    bool flag = false;
    while (!flag) {
        flag = true;
        for (Rank i = lo + 1; i < hi; i++) {
            if (_elem[i-1] > _elem[i]) {
                swap<T>(_elem[i-1], _elem[i]);
                flag = false;
            }
        }
        hi--;
    }
}
/*                  */
/* leaping version */
template <typename T>
void leap_bubbleSort(T* S, Rank lo, Rank hi) {
    Rank last;
    while (lo < hi) {
        last = lo;
        for (Rank i = lo + 1; i < hi; i++) {
            if (S[i-1] > S[i]) {
                swap<T>(S[i-1], S[i]);
                last = i;
            }
        }
        hi = last;
    }
}
/*                 */


template <typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    // use 'const' to ensure that A's elements will not be written
    _elem = new T[_capacity = max(DEFAULT_CAPACITY, hi-lo)<<1];
    for(_size = 0; lo < hi; _size++, lo++) {
        _elem[_size] = A[lo];
    }
}

template <typename T>
Rank Vector<T>::deduplicate() {
    Rank old_size = _size;
    for (Rank i = 1; i < _size; i++) {
        if (-1 != find(_elem[i], 0, i)) {
            remove(i);
        }
    }
    return old_size - _size;
}


template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) {return;}
    //printf(".....expanding\n");
    _capacity = max(_capacity, DEFAULT_CAPACITY);
    T* old_elem = _elem;
    _elem = new T[_capacity <<= 1];
    for(Rank i = 0; i < _size; i++) {
        _elem[i] = old_elem[i];
    }
    delete [] old_elem;
}

template <typename T>
Rank Vector<T>::find (T const& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (_elem[hi] != e));
    return hi;
}


template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
    expand();
    for(Rank i = _size; i > r; i--) {
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    _size++;
    return r;
}


template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo <= 1 ) {return;}
    Rank mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    // merge
    T* A = _elem + lo; Rank i = 0;
    Rank length_B = mi - lo; T* B = new T[length_B]; Rank j = 0;
    Rank length_C = hi - mi; T* C = _elem + mi ;Rank k = 0;
    for (Rank i = 0; i < length_B; i++) {
        B[i] = A[i];
    }
    while (j < length_B && k < length_C ) {
        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    }
    while (j < length_B) {
        A[i++] = B[j++];
    }
    delete [] B;
}


template <typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r+1);
    return e;
}

template <typename T>
Rank Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) {return 0;}
    while(hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}



/* binSearch version a */
template <typename T>
static Rank binSearch_a (T *S, T const& e, Rank lo, Rank hi) { // return the rank if e exists, else return rank -1
    // cannot return the highest rank of e (if there are multiple elements in T with value e)
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < S[mi]) {
            hi = mi;
        } else if (e > S[mi]) {
            lo = mi + 1;
        } else {
            return mi;
        }
    }
    return -1;
}
/*                     */
/* binSearch version b */
template <typename T>
static Rank binSearch_b (T *S, T const& e, Rank lo, Rank hi) {
    // If e doesn't exist, insert at rank 'search(e) + 1'
    while (hi - lo > 1) {
        Rank mi = (hi + lo) >> 1;
        e < S[mi] ? hi = mi : lo = mi;
    }
    return e < S[lo] ? lo - 1 : lo;
}
/*                     */
/* binSearch version c */
template <typename T>
static Rank binSearch_c (T* S, T const& e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        e < S[mi] ? hi = mi : lo = mi + 1;
    }
    return lo - 1;
}
/*                     */
/* fibSearch */
template <typename T>
static Rank fibSearch(T *S, T const& e, Rank lo, Rank hi) {
    // TODO
    return binSearch_c(S, e, lo, hi);
}

template <typename T>
Rank Vector<T>::search (T const& e, Rank lo, Rank hi) const {
    return (rand() % 2) ? binSearch_c (_elem, e, lo, hi) : fibSearch (_elem, e, lo, hi);
}



template <typename T>
void Vector<T>::shrink() {
    if (_size < (DEFAULT_CAPACITY<<1)) {return;}
    if ((_size << 2) > DEFAULT_CAPACITY) {return;}
    T* old_elem = _elem;
    _elem = new T[_capacity >>= 1];
    for( Rank i = 0; i<_size; i++) {
        _elem[i] = old_elem[i];
    }
    delete [] old_elem;
}


template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    // Choose algorithms randomly to test; Choose algorithm carefully in practice
    switch (rand() % 2) {
        case 0: {
            //printf("bubble\n");
            bubbleSort(lo, hi);
            break;
        }
        case 1: {
            //printf("merge\n");
            mergeSort(lo, hi);
            break;
        }
            //case 3: selectionSort(lo, hi); break;
            //case 4: heapSort(lo, hi);break;
            //case 5: quickSort(lo, hi); break;
            //default: shellSort(lo, hi); break;
    }
}

template <typename T>
void Vector<T>::traverse (void (*visit) (T&)){
    for (Rank i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
    for (Rank i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template <typename T>
Rank Vector<T>::uniquify() {
    Rank i = 0, j= 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j]) {
            _elem[++i]  = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j-i;
}
template <typename T>
void Vector<T>::heapSort (Rank lo, Rank hi) {
    T* A = _elem + lo;
    Rank n = hi - lo;
    PQ_ComplHeap<T>::heapify(A, n);
    while (0 < --n) {
        swap(A[0], A[n]);
        percolateDown(A, n, 0);
    }
}


/* LUG */
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi) {
    swap(_elem[lo], _elem[lo + rand()%(hi-lo)]);
    T pivot = _elem[lo];
    while (lo < hi) {
        do {hi--;} while ((lo < hi) && (pivot <= _elem[hi]));
        if (lo < hi) {_elem[lo], _elem[hi];}
        do {lo++;} while ((lo < hi) && (pivot >= _elem[lo]));
        if (lo < hi) { _elem[hi], _elem[lo];}
    } // lo == hi || lo == hi + 1
    _elem[hi] = pivot;
    return hi;
}
/* LGU */
/*
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi) {
    swap(_elem[0], _elem[lo + rand()%(hi-lo)]);
    T pivot = _elem[0];
    // L = (lo, mi], G = (mi, k), U = [k, hi)
    Rank mi = lo;
    for (Rank k = lo + 1; k < hi; k++) {
        if (_elem[k] < pivot) {
            swap(_elem[++mi], _elem[k]);
        }
    }
    swap(_elem[lo], _elem[mi]);
    return mi;

}
 */

template <typename T>
void Vector<T>::quickSort (Rank lo, Rank hi) {
    if (hi - lo < 2) {return;}
    Rank mi = partition(lo, hi);
    quickSort(lo, mi);
    quickSort(mi+1, hi);
}


