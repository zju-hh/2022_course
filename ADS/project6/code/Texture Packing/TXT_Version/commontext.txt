#ifndef __COMMONTEXT_H__
#define __COMMONTEXT_H__

//#define __MANUAL_INPUT__  //手工输入就激活该宏

//#define __TEST__        //测试模式就激活__TEST__
#ifdef __TEST__         
#define __INPUT_TEST__  //检测输入
#define __DEBUG_TEST__  //显示执行关键操作后，相关的信息变化
#define __INPUT_VIEW__  //显示输入的内容
#define __PLACE_ORDER__ //输出放置矩形顺序的文件
#endif

//下列宏请不要修改，因为程序的正常运行需要它们
#define __POSSIBLE_OPTIMIZATION__   //采用优化方案
#ifdef __POSSIBLE_OPTIMIZATION__
#define __SCORING_OPTIMIZATION__    //矩形得分环节优化
#define __PACKING_OPTIMIZATION__    //矩形定位环节优化
#endif

#define MAXAMOUNT 10000 //矩形最大数量
#define __NOT_FIT__ -1  //不合适，用在空间判定和分数判定上
#define __INFINITY_WH__ -1 //无穷大的墙高设定为-1，便于程序判断

#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief 空间单元结构体
 * @param x,y 空间左下角坐标
 * @param w,h1,h2 宽度，左墙高，右墙高
 * @param Former,Latter 前后空间指针
 */
typedef struct Space Sp;
struct Space
{
    int x, y;
    int w, h1, h2;
    Sp *Former;
    Sp *Latter;
};

/**
 * @brief 矩形结构体
 * @param x,y 矩形左下顶点坐标(int)
 * @param width,length 矩形宽高(int)
 * @param packed 是否已被打包(bool)
 *
 */
typedef struct Rec Rec;
struct Rec
{
    int x, y;
    int width, length;
    bool packed = false;
};

#endif