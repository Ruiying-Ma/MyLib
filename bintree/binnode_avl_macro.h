//
// Created by 马睿赢 on 2023/2/21.
//

#define Balanced( x ) ( stature( ( x ).lc ) == stature( ( x ).rc ) ) //理想平衡条件
#define BalFac( x ) ( stature( ( x ).lc ) - stature( ( x ).rc ) ) //平衡因子
#define AvlBalanced( x ) ( ( -2 < BalFac( x ) ) && ( BalFac( x ) < 2 ) ) // AVL平衡条件
