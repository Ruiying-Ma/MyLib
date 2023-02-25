//
// Created by 马睿赢 on 2023/2/24.
//

#ifndef MY_LIB_PQ_COMPLETEHEAP_MACRO_H
#define MY_LIB_PQ_COMPLETEHEAP_MACRO_H

#define Parent(i) (((i)-1)>>1)
#define LChild(i) (1 + ((i)<<1))
#define RChild(i) (2 + ((i)<<1))
#define InHeap(n, i) (((-1) != (i)) &&((i)<(n)))
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) ((PQ[i] < PQ[j]) ? j : i )
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
         ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
         ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
         ) \
         ) //相等时父节点优先，如此可避免不必要的交换

#endif //MY_LIB_PQ_COMPLETEHEAP_MACRO_H
