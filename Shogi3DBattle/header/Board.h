#pragma once

#include"B_GameObj.h"
#include<map>

class Board : public B_GameObj
{
private:
    std::map<GameObjType, float> _boardSizeMap =
    {
        {GameObjType::BOARD_55,  60.0f},
        {GameObjType::BOARD_99, 100.0f}
    };

public:
    void ChangeBoard(GameObjType board); // «Šû”Õ‚ğ•ÏX
};