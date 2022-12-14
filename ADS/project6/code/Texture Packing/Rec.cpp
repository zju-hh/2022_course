//#include "commontext.h"
#include "Rec.h"

RecClass::RecClass(int n)
{
    amount = n;
    minwidth = 9999999;
    static Rec RecArray[MAXAMOUNT];
    r = RecArray;
    ScoreListReset();
    ReadInRecInfo();
}

/**
 * @brief 读入所有待加入矩形信息: 手动输入就调用宏__MANUAL_INPUT__，否则就不调用;同时还将输入的矩形进行“宽度递减，高度递减”原则排序
 *
 */
void RecClass::ReadInRecInfo()
{
    //手动输入就调用宏__MANUAL_INPUT__
#ifdef __MANUAL_INPUT__
    int i;
    for (i = 0; i < amount; i++)
    {
        r[i].x = (r[i].y = 0);
        r[i].packed = false;
        cin >> r[i].width >> r[i].length;
#ifdef __INPUT_VIEW__
        cout << r[i].x << ' ' << r[i].y << ' ' << r[i].width << ' ' << r[i].length << endl;
#endif
        if (minwidth > r[i].width)
            minwidth = r[i].width;
    }
#ifdef __INPUT_VIEW__
    cout << "minwidth is :" << minwidth << endl;
#endif

#endif
    //读取txt文档来实现输入就取消调用__MANUAL_INPUT__
#ifndef __MANUAL_INPUT__
    fstream f("TestCase\\data.txt", ios::in);
    int temp = 0;
    f >> temp >> amount;
    int i;
    for (i = 0; i < amount; i++)
    {
        f >> r[i].width >> r[i].length;
/*
#ifdef __INPUT_VIEW__
        cout << r[i].x << ' ' << r[i].y << ' ' << r[i].width << ' ' << r[i].length << endl;
#endif
*/
        if (minwidth > r[i].width)
            minwidth = r[i].width;
    }
#ifdef __INPUT_VIEW__
    cout << "minwidth is :" << minwidth << endl;
#endif
    f.close();
#endif

    //至此输入结束，下面进行排序
    WidthSort();
#ifdef __INPUT_VIEW__
    fstream f("TestCase\\Sorted.txt",ios::out);
    int i;
    for(i=0;i<amount;i++)
    {
        f<<r[i].width<<' '<<r[i].length<<'\n';
    }
    f.close();
#endif
}

/**
 * @brief 重置矩形得分表
 *
 */
void RecClass::ScoreListReset()
{
    int i;
    for (i = 0; i < amount; i++)
        ScoreList[i] = -1;
}

/**
 * @brief 根据匹配情况，返回对应的分数，一共有5种情形，分值从0到4
 *
 * @param R 表示被选矩形
 * @param S 表示被选的放置空间
 * @return int 矩形得分
 */
int RecClass::Score(Rec R, Sp *S)
{
    int width = R.width, length = R.length;
    int w = S->w;

    if (width == w)
    {
        if (length == S->h1 || length == S->h2) //正好契合，我们给最高分4分
            return 4;
        if (length > max(S->h1, S->h2)) //高出一截，我们给3分,首次插入的最佳赋值就是这种情况,即两侧墙无穷高，但是宽度匹配
            return 3;
        else //剩下就是不凸出同时不完全契合的，我们给2分
            return 2;
    }
    else if (width < w)
    {
        if (length == S->h1 || length == S->h2) //高度和某一墙契合，我们给1分
            return 1;
        else //剩下完全不匹配情况，我们给0分
            return 0;
    }
    else
    {
#ifdef __DEBUG_TEST__
        cout << "The rectangle is wider than container!!!" << endl;
#endif
        // exit(1);
        return __NOT_FIT__;
    }
}

/**
 * @brief 从得分表中获取第一个得分为score的矩形编号,如果没有找到，暂时停机
 *
 * @param score 得分
 * @return int
 */
int RecClass::GivenScoreRecID(int score)
{
    int i;
    bool IsFound = false;
    for (i = 0; i < amount; i++)
    {
        if (ScoreList[i] == score)
        {
            IsFound = true;
            break;
        }
    }
    if (!IsFound)
    {
        cout << "Not Found!!!" << endl;
        system("pause");
    }
    return i;
}

/**
 * @brief 将给定矩形靠左放置，确定矩形左下角顶点的坐标
 *
 * @param R 给定矩形
 * @param s 指定空间
 */
void RecClass::PackToLeft(Rec &R, Sp *S)
{
    R.x = S->x, R.y = S->y;
    R.packed = true;
#ifdef __PLACE_ORDER__
    fstream f("TestCase\\Order.txt", ios::app);
    f << R.x << ' ' << R.y << ' ' << R.width << ' ' << R.length << '\n';
    f.close();
#endif
}

/**
 * @brief 将给定矩形靠右放置，确定矩形左下角顶点的坐标
 *
 * @param R 给定矩形
 * @param s 指定空间
 */
void RecClass::PackToRight(Rec &R, Sp *S)
{
    R.x = S->x + S->w - R.width, R.y = S->y;
    R.packed = true;
#ifdef __PLACE_ORDER__
    fstream f("TestCase\\Order.txt", ios::app);
    f << R.x << ' ' << R.y << ' ' << R.width << ' ' << R.length << '\n';
    f.close();
#endif
}

/**
 * @brief   更新未Packed矩形的最小宽度
 *
 */
void RecClass::FreshMinWidth()
{
    int i;
    int min = 9999999;
    for (i = 0; i < amount; i++)
    {
        if (min > r[i].width && r[i].packed == false)
            min = r[i].width;
    }
    minwidth = min;
}

/**
 * @brief 将矩形序列排按照“宽度大优先，高度高优先”的原则排序
 *
 */
void RecClass::WidthSort()
{
    int i, j;
    for (i = 0; i < amount; i++)
    {
        for (j = i + 1; j < amount; j++)
        {
            if ((r[i].width < r[j].width) || ((r[i].width == r[j].width) && (r[i].length < r[j].length)))
            {
                swap(r[i], r[j]);
            }
        }
    }
}