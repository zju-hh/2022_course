#ifndef __SPACE_H__
#define __SPACE_H__
#include "commontext.h"
#include "Rec.h"

class RecClass;

class SpaceClass
{
public:
    int MaxWidth;
    int amount;
    
    Sp *Sp_Head;

public:
    // SpaceClass();
    SpaceClass(int m=40);
    Sp *LL_SpaceChoose();
    void UpdateSpaceSet(int ID,int score, RecClass &RC, Sp *s);
    void DeleteSpace(Sp *s);
    Sp *AddSpace(Sp *s);
};

#endif