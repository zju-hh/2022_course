#ifndef __USEDSTRUCT_H__
#define __USEDSTRUCT_H__
/**
 * @brief �ռ䵥Ԫ�ṹ��
 * @param x,y �ռ����½�����
 * @param w,h1,h2 ��ȣ���ǽ�ߣ���ǽ��
 * @param Former,Latter ǰ��ռ�ָ��
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
 * @brief ���νṹ��
 * @param x,y �������¶�������(int)
 * @param width,length ���ο��(int)
 * @param packed �Ƿ��ѱ����(bool)
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