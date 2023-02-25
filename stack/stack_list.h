//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_STACK_LIST_H
#define MY_LIB_STACK_LIST_H
#include "../list/list.h"
template <typename T> class stack : public List<T> {
public:
    void push (T const& e) {List<T>::insertAsLast(e);}
    T pop() {return List<T>::remove(List<T>::last());}
    T& top() {return (List<T>::last())->data;}
};
#endif //MY_LIB_STACK_LIST_H
