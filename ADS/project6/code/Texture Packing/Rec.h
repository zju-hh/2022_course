#ifndef __REC_H__
#define __REC_H__
#include "commontext.h"
#include "Space.h"

class RecClass
{
public:
    int amount;
    int minwidth;
    Rec *r;
    int ScoreList[MAXAMOUNT];

    RecClass(int n=0);
    
    void ReadInRecInfo();
    void ScoreListReset();
    int Score(Rec R, Sp* S);
    int GivenScoreRecID(int score);
    void PackToLeft(Rec &R, Sp* S);
    void PackToRight(Rec &R, Sp* S);
    void FreshMinWidth();
    void WidthSort();
};

#endif
