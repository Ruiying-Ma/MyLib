//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_QUEUE_H
#define MY_LIB_QUEUE_H

#include "../list/list.h"
template <typename T> class Queue : public List<T> {
public:
    void enqueue (T const& e) {List<T>::insertAsLast(e);}
    T dequeue () {return List<T>::remove(List<T>::last());}
    T& front() {return (List<T>::first())->data;}
};

#endif //MY_LIB_QUEUE_H
