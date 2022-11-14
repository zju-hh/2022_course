#include "commontext.h"
#include "Rec.h"
#include "Space.h"

class Given_Info
{
public:
    int amount;
    int MaxWidth;
    SpaceClass SC;
    RecClass RC;
    Given_Info()
    {
#ifdef __MANUAL_INPUT__
        cout << "Please input the MaxWidth and Rectangle amount:" << endl;
        cin >> MaxWidth >> amount;
        RecClass RC(amount);
        SpaceClass SC(MaxWidth);
#endif
    }
};

int HeuristicPacking(Given_Info Info);
void OutputFile(RecClass &R, SpaceClass &S);
Given_Info Info;

int main()
{
    int h = __INFINITY_WH__;

    h = HeuristicPacking(Info);
    cout << "The min height is: " << h << endl;
    OutputFile(Info.RC, Info.SC);
    system("pause");
    return 0;
}

/**
 * @brief 根据给定的已排序好的矩形序列 X 生成放置方案，返回该方案对应的总高度h
 * @param 信息集合对象 包含各种信息
 * @return 堆叠高度
 */
int HeuristicPacking(Given_Info Info)
{
    int h = 0, pin = 0; // h为总高度，pin为已经打包好的矩形数量
    int i, n = Info.RC.amount;
    // int *ScoreList = Info.RC.ScoreList;
    int maxscore = -1;
    Sp *s;
    Rec *r = Info.RC.r;
    while (pin < n)
    {
        maxscore = -1;
        s = Info.SC.LL_SpaceChoose(); //找到最低、最左的放置空间s

        if (s->w >= Info.RC.minwidth)
        {
            //下面为采用了优化后的矩形选取方法，直接记录第一个最高分矩形的ID，如果得分达到4，直接打包该矩形
#ifdef __SCORING_OPTIMIZATION__
            int R = -1; //得分最高矩形的编号ID
            int CurrentScore = 0;
            for (i = 0; i < n; i++)
            {
                if (r[i].packed == true)
                    continue;
                CurrentScore = Info.RC.Score(r[i], s); //对当前矩形得分进行评估
                if (maxscore < CurrentScore)
                {
                    maxscore = CurrentScore;
                    R = i;
                    if (maxscore == 4) //最高得分直接跳出即可
                        break;
                }
            }
#endif

#ifndef __SCORING_OPTIMIZATION__
            for (i = 0; i < n; i++)
            {
                if (r[i].packed == true)
                    continue;
                ScoreList[i] = Info.RC.Score(r[i], s); //对当前矩形得分进行评估，将结果保存到得分表ScoreList中。
                if (maxscore < ScoreList[i])
                    maxscore = ScoreList[i];
            }
            int R = Info.RC.GivenScoreRecID(maxscore); //获取得分最高矩形的编号ID
#endif

            pin++;                      //这个时候我们已经选好放置的矩形了，接下来是将它的位置固定
            if (s->y + r[R].length > h) //当前总高比放置矩形后的高度小，就更新总高
            {
                h = s->y + r[R].length;
            }
            Info.SC.UpdateSpaceSet(R, maxscore, Info.RC, s);

            //如果刚刚加入的矩形是所有待packing中宽度最小的，就更新最小宽度
            if (r[R].width == Info.RC.minwidth)
                Info.RC.FreshMinWidth();
#ifdef __PSEUDO_VERSION__
            if (s->h1 >= s->h2)
            {
                Info.RC.PackToLeft(r[R], s); //靠左放置
                Info.SC.UpdateSpaceSet(R, Info.RC, s);
            }
            else
            {
                Info.RC.PackToRight(r[R], s); //靠右放置
                Info.SC.UpdateSpaceSet(R, Info.RC, s);
            }
#endif
        }
        else
        {
            Info.SC.UpdateSpaceSet(__NOT_FIT__, __NOT_FIT__, Info.RC, s);
        }
    }
    return h;
}

void OutputFile(RecClass &R, SpaceClass &S)
{
    fstream f("TestCase\\result.txt", ios::out);
    f << S.MaxWidth << " " << R.amount << '\n';
    int i;
    for (i = 0; i < R.amount; i++)
    {
        f << R.r[i].x << ' ' << R.r[i].y << ' ' << R.r[i].width << ' ' << R.r[i].length << '\n';
    }
    f.close();
}