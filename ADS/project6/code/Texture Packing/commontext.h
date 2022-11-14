#ifndef __COMMONTEXT_H__
#define __COMMONTEXT_H__

//#define __MANUAL_INPUT__  //�ֹ�����ͼ���ú�

//#define __TEST__        //����ģʽ�ͼ���__TEST__
#ifdef __TEST__         
#define __INPUT_TEST__  //�������
#define __DEBUG_TEST__  //��ʾִ�йؼ���������ص���Ϣ�仯
#define __INPUT_VIEW__  //��ʾ���������
#define __PLACE_ORDER__ //������þ���˳����ļ�
#endif

//���к��벻Ҫ�޸ģ���Ϊ���������������Ҫ����
#define __POSSIBLE_OPTIMIZATION__   //�����Ż�����
#ifdef __POSSIBLE_OPTIMIZATION__
#define __SCORING_OPTIMIZATION__    //���ε÷ֻ����Ż�
#define __PACKING_OPTIMIZATION__    //���ζ�λ�����Ż�
#endif

#define MAXAMOUNT 10000 //�����������
#define __NOT_FIT__ -1  //�����ʣ����ڿռ��ж��ͷ����ж���
#define __INFINITY_WH__ -1 //������ǽ���趨Ϊ-1�����ڳ����ж�

#include <iostream>
#include <fstream>
using namespace std;

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