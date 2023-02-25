//
// Created by 马睿赢 on 2023/2/21.
//

#ifndef MY_LIB_AVL_MACRO_H
#define MY_LIB_AVL_MACRO_H

/******************************************************************************************
 * 在左、右孩子中取更高者
 * 在AVL平衡调整前，借此确定重构方案
 ******************************************************************************************/
#define tallerChild(x) ( \
  stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*左高*/ \
  stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*右高*/ \
  IsLChild( * (x) ) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
  ) \
  ) \
)

#endif //MY_LIB_AVL_MACRO_H
