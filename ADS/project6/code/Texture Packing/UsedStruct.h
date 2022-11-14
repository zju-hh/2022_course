#ifndef __USEDSTRUCT_H__
#define __USEDSTRUCT_H__
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