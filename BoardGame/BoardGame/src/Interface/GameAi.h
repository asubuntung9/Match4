// GameAi.h
#pragma once
#include "Types.h"

class Board;

class GameAi
{
protected:
    Board* m_pBoard;

public:
    GameAi(Board* pBoard) : m_pBoard(pBoard) { }
    virtual ~GameAi() { }

    // Returns the best move for the current board state.
    virtual Move FindBestMove() = 0;
};
