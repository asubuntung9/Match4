// MinMaxAi.h
#pragma once

#include "../Interface/GameAi.h"

//---------------------------------------------------------------------------------------------------------------------
// This AI just chooses a random valid move and makes it.
//---------------------------------------------------------------------------------------------------------------------
class MinMaxAi : public GameAi
{
    static constexpr int k_maxDepth = 5;
public:
    MinMaxAi(Board* pBoard) : GameAi(pBoard){ }
    virtual Move FindBestMove() override;
    int Minimax(int depth, bool isMaximizingPlayer, int alpha, int beta);
    int Evaluate(int depth);

};
