//
// Created by 马睿赢 on 2023/2/21.
//

#ifndef MY_LIB_UTIL_H
#define MY_LIB_UTIL_H
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <typeinfo>
#include <assert.h>
//#include "comparator.h"
//#include "checkOrder_Elem.h"
//#include "checkOrder_list.h"
//#include "checkOrder_vector.h"
//#include "double_Elem.h"
//#include "increase_Elem.h"
//#include "hailstone_Elem.h"
//#include "increase_list.h"
//#include "increase_vector.h"
//#include "crc_Elem.h"
//#include "crc_list.h"
//#include "crc_vector.h"
//#include "rand.h" //随机数

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#if defined(DSA_DEBUG) //编译开关，控制调试输出
#define DSA(x)  { x } //输出
#else
#define DSA(x) //不输出
#endif
#endif //MY_LIB_UTIL_H
