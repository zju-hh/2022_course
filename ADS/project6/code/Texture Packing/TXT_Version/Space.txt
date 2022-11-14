#include "commontext.h"
#include "Space.h"
#include "Rec.h"

SpaceClass::SpaceClass(int m)
{
#ifdef __MANUAL_INPUT__
    MaxWidth = m;
#endif
#ifndef __MANUAL_INPUT__
    fstream f("TestCase\\data.txt", ios::in);
    f >> MaxWidth;
    f.close();
#ifdef __INPUT_VIEW__
    cout << "MaxWidth is :" << MaxWidth << endl;
#endif

#endif
    amount = 1;
    Sp_Head = new Sp;
    Sp_Head->Former = Sp_Head;
    Sp_Head->Latter = new Sp;
    Sp *first = Sp_Head->Latter;
    //下面是第一个空间信息的初始化
    first->Former = Sp_Head;
    first->Latter = NULL;
    first->h1 = __INFINITY_WH__;
    first->h2 = __INFINITY_WH__;
    first->w = MaxWidth;
    first->x = 0, first->y = 0;
}

/**
 * @brief 选择最低的空间，同低取最左
 *
 * @return Sp* 最低空间的指针
 */
Sp *SpaceClass::LL_SpaceChoose()
{
    Sp *SpChosen = Sp_Head->Latter;
    Sp *temp = Sp_Head;
    for (temp = temp->Latter; temp != NULL; temp = temp->Latter)
    {
        if ((SpChosen->y > temp->y) || (SpChosen->y == temp->y && SpChosen->x > temp->x)) //越低优先，同高越左优先
            SpChosen = temp;
    }
    if (SpChosen->h1 <= 0)
        SpChosen->h1 = __INFINITY_WH__;
    if (SpChosen->h2 <= 0)
        SpChosen->h2 = __INFINITY_WH__;

#ifdef __DEBUG_TEST__
    cout << "\nCurrent Space Status:\n==================================" << endl;
    Sp *current = NULL;
    int count = 0;
    for (current = Sp_Head->Latter; current != NULL; current = current->Latter)
    {
        printf("Space %d: %d %d %d %d %d\n", ++count, current->x, current->y, current->w, current->h1, current->h2);
    }
    cout << "============================\n"
         << endl;
    printf("Chosen Space Info: %d %d %d %d %d\n", SpChosen->x, SpChosen->y, SpChosen->w, SpChosen->h1, SpChosen->h2);
#endif

    return SpChosen;
}

/**
 * @brief 从双向链表中删除指定空间单元，同时处理好前后单元联系
 *
 * @param S 指定空间单元
 */
void SpaceClass::DeleteSpace(Sp *S)
{
#ifdef __DEBUG_TEST__
    if (S == NULL)
    {
        cout << "ERROR Delete!!!" << endl;

        system("pause");

        exit(1);
    }
#ifdef __INPUT_TEST__
    else
    {
        printf("Deleted.Info: %d %d %d %d %d \n", S->x, S->y, S->w, S->h1, S->h2);
    }
#endif
#endif
    S->Former->Latter = S->Latter;
    if (S->Latter != NULL)
        S->Latter->Former = S->Former;
    delete S;
}

/**
 * @brief 采用双向链表的前插法，在指定空间的前面加入新空间,
 *
 * @param S 指定空间
 * @return NewSpace 新空间的指针
 */
Sp *SpaceClass::AddSpace(Sp *S)
{
    Sp *NewSpace = new Sp;
    NewSpace->Former = S->Former;
    NewSpace->Latter = S;
    S->Former->Latter = NewSpace;
    S->Former = NewSpace;
    amount++;
    return NewSpace;
}

/**
 * @brief 该函数实现放置矩形后对插入位置的空间信息进行更新,依据是矩形的得分情况
 * @param R  :插入矩形的代号
 * @param RC :矩形信息类
 * @param S  :插入空间的指针
 */
void SpaceClass::UpdateSpaceSet(int R, int score, RecClass &RC, Sp *S)
{
    static int count = 0; //标记当前加入第几个矩形
    count++;

    int h1 = S->h1, h2 = S->h2; // h1,h2为当前空间最开始的左，右墙
    int length = 0;             //被选矩形的高度
    int width = 0;              //被选矩形的宽度
    if (R != __NOT_FIT__)
    {
        length = RC.r[R].length; //被选矩形的高度
        width = RC.r[R].width;   //被选矩形的宽度
    }

    int *HWH = &(S->h1), *LWH = &(S->h2);      // HWH and LWH stand for higher-wall-height and lower-wall-height pointer.
    Sp *HW_Sp = S->Former, *LW_Sp = S->Latter; // HW_sp与LW_sp分别表示Higher-wall-space and Lower-wall-space
    if (h1 < h2 && h1 != __INFINITY_WH__)
    {
        swap(HWH, LWH);
        swap(HW_Sp, LW_Sp);
    }
#ifdef __DEBUG_TEST__

    cout << "No." << count << " Rec Info:" << width << " " << length << endl;
    cout << "The Score is:" << score << endl;
#endif

    //这里使用矩形得分来确定空间的更新方式
    switch (score)
    {
    case 4:
    {
#ifdef __PACKING_OPTIMIZATION__
        //由于是完全匹配，我们先将矩形的位置确定，再进行空间信息的更新
        //只需要将矩形的左下角与空间最左点重合即可，也即是往左打包
        RC.PackToLeft(RC.r[R], S);
        //随后进行空间的合并
#endif
        if (length == h1 && h1 <= h2) //如果矩形宽度与左墙同高，同时左墙不高于右墙时，我们就将左侧空间与当前空间合并,
        {
            S->w += S->Former->w;
            //这里我们选择修改空间定位点，然后删除掉前一个空间就好
            S->x = S->Former->x; //空间横坐标平移
            S->y = S->Former->y;
            S->h1 = S->Former->h1;
            S->h2 = ((h2 - h1) == 0) ? S->Latter->h2 : h2 - h1; //如果同高，则右墙高度与右空间右墙同高，否则为h2-h1(>0)
            //至此合并结束，下一步删除左侧空间
            DeleteSpace(S->Former);
            amount--; //总空间数减少
        }
        if (length == h2) //如果矩形高度还与右侧同高，我们就将右侧空间与当前空间合并
        {
            S->w += S->Latter->w;
            //由于空间定位点不发生改变，所以只需要修改y即可
            S->y = S->Latter->y;
            if (h1 > h2) //如果最开始的空间两墙同高，则左墙高度在上一个if已经确定好了，否则变为h1-h2(>0)
                S->h1 = h1 - h2;
            S->h2 = S->Latter->h2;
            //至此合并结束，下一步删除右侧空间
            DeleteSpace(S->Latter);
            amount--; //总空间数减少
        }
        //至此，操作完成
        break;
    }
    case 3: // 3分情况：宽度匹配，高度不同，表现为凸出一截
    {
#ifdef __PACKING_OPTIMIZATION__
        //由于宽度是完全匹配，矩形的位置很容易就可以确定
        //只需要将矩形的左下角与空间最左点重合即可，也即是往左打包
        RC.PackToLeft(RC.r[R], S);
        //随后进行空间信息的修改
#endif
        S->y = S->y + length;
        if (S->h1 != __INFINITY_WH__)
        {
            S->Former->h2 = length - S->h1;
        }
        if (S->h2 != __INFINITY_WH__)
        {
            S->Latter->h1 = length - S->h2;
        }
        S->h1 = __INFINITY_WH__; //由于加入这个矩形以后相当于凸出一块，所以它的两墙高度为无穷
        S->h2 = __INFINITY_WH__;
        break;
    }
    case 2: // 2分情况：宽度匹配，高度比墙低，无穷高的墙体视作最低墙
        //在该情况中，不会出现两侧墙体同时为无穷高
        {
#ifdef __PACKING_OPTIMIZATION__
            //由于宽度是完全匹配，矩形的位置很容易就可以确定
            //只需要将矩形的左下角与空间最左点重合即可，也即是往左打包
            RC.PackToLeft(RC.r[R], S);
            //随后进行空间信息的修改
#endif
            //这里的高低墙是指非无穷条件下的高低，如果有一墙为无穷高，那么它会被视为最低.

            if (length > *LWH && *LWH != __INFINITY_WH__) //高度大于低墙,同时低墙非无穷高
            {
                //先修改相邻空间的墙高
                if (LW_Sp == S->Latter) //如果低墙对应空间为当前空间的右空间，则更新低墙空间的左墙
                {
                    LW_Sp->h1 = length - *LWH;
                }
                else //低墙对应空间为左空间，则更新左空间的右墙
                {
                    LW_Sp->h2 = length - *LWH;
                }
                //修改完相邻空间墙高后，还需要修改当前空间信息
                S->y += length;         //空间纵坐标上移
                *HWH -= length;         //较高墙修改
                *LWH = __INFINITY_WH__; //较低墙变为无穷高
            }
            else //高度小于低墙，相当于只是空间填充了一部分，相邻空间墙体不发生改变
            {
                S->y += length;
                *HWH -= length;
                *LWH -= length;
            }
            break;
        }
    case 1: //特征：宽度不匹配，但是匹配一侧墙高
    {

        if (length == h1) //靠左墙放置，修改当前空间的起始点
        {
#ifdef __PACKING_OPTIMIZATION__
            RC.PackToLeft(RC.r[R], S);
#endif
            S->Former->w += width;
            S->w -= width;
            S->x += width;
        }
        else if (length == h2) //靠右墙放置，修改右空间起始点
        {
#ifdef __PACKING_OPTIMIZATION__
            RC.PackToRight(RC.r[R], S);
#endif
            S->Latter->w += width;
            S->Latter->x -= width;
            S->w -= width;
        }
        else
        {
            cout << "1 point matching gaines ERROR!!!" << endl;
            system("pause");
            exit(1);
        }
        break;
    }
    case 0: //特征：完全不匹配,统一往较高墙体靠......
    {
        unsigned int ofs_L = h1, ofs_R = h2; // ofs用来将无穷高具体化

        if (ofs_L >= ofs_R)
        {
#ifdef __PACKING_OPTIMIZATION__
            RC.PackToLeft(RC.r[R], S);
#endif
            S->w -= width, S->x += width, S->h1 = length;                      //空间定位点右移
            S->Former->h2 = ((length < h1) ? __INFINITY_WH__ : (length - h1)); //这里length-h1不会为0,因为相等情况的得分最少为1
            Sp *NewSpace = AddSpace(S);                                        //因为矩形向左靠，我们就在当前空间左边增加新空间
            NewSpace->x = RC.r[R].x;                                           //新空间坐标与矩形定位点重合
            NewSpace->y = RC.r[R].y + length;
            NewSpace->w = width;
            NewSpace->h1 = ((length < h1) ? (h1 - length) : __INFINITY_WH__); //新空间左墙高度为相对差值
            NewSpace->h2 = __INFINITY_WH__;                                   //右墙高度为无穷
        }
        else
        {
#ifdef __PACKING_OPTIMIZATION__
            RC.PackToRight(RC.r[R], S);
#endif
            S->w -= width, S->h2 = length; //由于矩形向右靠，当前空间的定位点就无需平移
            //由于我们AddSpace函数为前插函数，需要检查是否存在右空间
            if (S->Latter != NULL) //存在右空间
            {
                S->Latter->h1 = ((length < h2) ? __INFINITY_WH__ : (length - h2)); //这里length-h2不会为0,因为相等情况的得分最少为1
                Sp *NewSpace = AddSpace(S->Latter);                                //增加新空间
                NewSpace->x = RC.r[R].x;
                NewSpace->y = RC.r[R].y + length;
                NewSpace->w = width;
                NewSpace->h1 = __INFINITY_WH__;                                   //新空间左墙高度为无穷
                NewSpace->h2 = ((length < h2) ? (h2 - length) : __INFINITY_WH__); //右墙高度为相对差值
            }
            else //不存在右空间，则直接在右侧加入新空间
            {
                //创建并联系新空间
                Sp *NewSpace = new Sp;
                NewSpace->Former = S;
                NewSpace->Latter = NULL;
                S->Latter = NewSpace;
                amount++;

                NewSpace->x = RC.r[R].x;
                NewSpace->y = RC.r[R].y + length;
                NewSpace->w = width;
                NewSpace->h1 = __INFINITY_WH__; //新空间左墙高度为无穷
                NewSpace->h2 = __INFINITY_WH__; //右墙高度为无穷
            }
        }
        break;
    }
    default: //无法放入矩形
    {
        count--;                                          //不加入矩形
        bool a[2] = {false};                              // 0，1代表左右墙，bool值表示是否合并
        unsigned int Height_Left = h1, Height_Right = h2; //无符号转化，-1对应的无穷大变为理论最大高
        if (Height_Left < Height_Right)
            a[0] = true;
        if (Height_Left > Height_Right)
            a[1] = true;
        if (h1 == h2 && h1 != -1)
            a[0] = true, a[1] = true;

        if (a[0]) //左侧合并
        {
            S->w += S->Former->w;
            S->x = S->Former->x;
            S->y = S->Former->y;
            S->h1 = S->Former->h1;
            S->h2 = h2 - h1; //至此合并结束，下一步删除左侧空间
            DeleteSpace(S->Former);
            amount--; //总空间数减少
        }
        if (a[1]) //右侧合并
        {
            S->w += S->Latter->w;
            S->y = S->Latter->y;
            if (!a[0])//如果是同高情况，那么当前空间的左墙高度在之前已经确定，这里就不再修改
                S->h1 = h1 - h2;
            S->h2 = S->Latter->h2; //至此合并结束，下一步删除右侧空间
            DeleteSpace(S->Latter);
            amount--; //总空间数减少
        }
    }
    }
}