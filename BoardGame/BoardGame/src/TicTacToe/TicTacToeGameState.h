// TicTacToeGameState.h
#pragma once

#include "../Interface/GameState.h"
#include "../Interface/Types.h"
#include "TicTacToeTypes.h"

class TicTacToeGameState : public GameState
{
    static constexpr int kBoardWidth = 3;
    static constexpr int kBoardHeight = 3;
    static constexpr size_t kBoardArraySize = kBoardWidth * kBoardHeight;
    static constexpr int kWinCount = 3;  // how many we need in a row

public:
    static constexpr int kMaxMoves = kBoardArraySize;

private:
    TicTacToeCellState m_cells[kBoardArraySize];

public:
    TicTacToeGameState();
    void Clear();

    int CheckForWinner() const;
    void MakeMove(const Move& move);
    void ResetMove(const int& index);
    TicTacToeCellState GetCellAtIndex(unsigned int index) const { return m_cells[index]; }
    void Draw() const;
    Moves GetLegalMoves(int playerIndex) const;


    virtual unsigned int GetHash() const override;

private:
    int GetIndexFromPos(int x, int y) const { return (y * kBoardWidth) + x; }
};
