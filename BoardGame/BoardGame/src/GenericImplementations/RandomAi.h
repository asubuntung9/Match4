// RandomAi.h
#pragma once

#include "../Interface/GameAi.h"

//---------------------------------------------------------------------------------------------------------------------
// This AI just chooses a random valid move and makes it.
//---------------------------------------------------------------------------------------------------------------------
class RandomAi : public GameAi
{
public:
    RandomAi(Board* pBoard) : GameAi(pBoard) { }

    virtual Move FindBestMove() override;
};
