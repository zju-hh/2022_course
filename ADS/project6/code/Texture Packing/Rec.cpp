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
 * @brief �������д����������Ϣ: �ֶ�����͵��ú�__MANUAL_INPUT__������Ͳ�����;ͬʱ��������ľ��ν��С����ȵݼ����߶ȵݼ���ԭ������
 *
 */
void RecClass::ReadInRecInfo()
{
    //�ֶ�����͵��ú�__MANUAL_INPUT__
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
    //��ȡtxt�ĵ���ʵ�������ȡ������__MANUAL_INPUT__
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

    //������������������������
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
 * @brief ���þ��ε÷ֱ�
 *
 */
void RecClass::ScoreListReset()
{
    int i;
    for (i = 0; i < amount; i++)
        ScoreList[i] = -1;
}

/**
 * @brief ����ƥ����������ض�Ӧ�ķ�����һ����5�����Σ���ֵ��0��4
 *
 * @param R ��ʾ��ѡ����
 * @param S ��ʾ��ѡ�ķ��ÿռ�
 * @return int ���ε÷�
 */
int RecClass::Score(Rec R, Sp *S)
{
    int width = R.width, length = R.length;
    int w = S->w;

    if (width == w)
    {
        if (length == S->h1 || length == S->h2) //�������ϣ����Ǹ���߷�4��
            return 4;
        if (length > max(S->h1, S->h2)) //�߳�һ�أ����Ǹ�3��,�״β������Ѹ�ֵ�����������,������ǽ����ߣ����ǿ���ƥ��
            return 3;
        else //ʣ�¾��ǲ�͹��ͬʱ����ȫ���ϵģ����Ǹ�2��
            return 2;
    }
    else if (width < w)
    {
        if (length == S->h1 || length == S->h2) //�߶Ⱥ�ĳһǽ���ϣ����Ǹ�1��
            return 1;
        else //ʣ����ȫ��ƥ����������Ǹ�0��
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
 * @brief �ӵ÷ֱ��л�ȡ��һ���÷�Ϊscore�ľ��α��,���û���ҵ�����ʱͣ��
 *
 * @param score �÷�
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
 * @brief ���������ο�����ã�ȷ���������½Ƕ��������
 *
 * @param R ��������
 * @param s ָ���ռ�
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
 * @brief ���������ο��ҷ��ã�ȷ���������½Ƕ��������
 *
 * @param R ��������
 * @param s ָ���ռ�
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
 * @brief   ����δPacked���ε���С����
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
 * @brief �����������Ű��ա����ȴ����ȣ��߶ȸ����ȡ���ԭ������
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