//
// Created by 马睿赢 on 2023/2/24.
//

#ifndef MY_LIB_PQ_H
#define MY_LIB_PQ_H
template <typename T> struct PQ {
    virtual void insert(T) = 0;
    virtual T getMax() = 0;
    virtual T delMax() = 0;
};


#endif //MY_LIB_PQ_H
