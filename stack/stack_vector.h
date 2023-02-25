//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_STACK_VECTOR_H
#define MY_LIB_STACK_VECTOR_H

#include "../vector/vector.h"
template <typename T> class Stack : public Vector<T>  {
public:
    void push(T const &e) {Vector<T>::insert(e);}
    T pop() {return Vector<T>::remove(Vector<T>::size()-1);}
    T& top() {return (*this)[Vector<T>::size()-1];}
};


#endif //MY_LIB_STACK_VECTOR_H
