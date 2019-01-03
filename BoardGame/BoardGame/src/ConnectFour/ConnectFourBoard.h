// ConnectFourBoard.h
#pragma once

#include "../Interface/Board.h"
#include "ConnectFourGameState.h"

//class ConnectFourGameState;

class ConnectFourBoard : public Board
{
    enum class Player : unsigned char
    {
        kRed = 1,  // must be 1, since it corresponds to player 1
        kBlack = 2,  // must be 2, since it corresponds to player 2
    };

    ConnectFourGameState m_currentState;
    Player m_currentPlayer;

public:
    ConnectFourBoard();

    virtual void StartGame() override;
    virtual int GetCurrentPlayer() const override { return (int)m_currentPlayer; }
    virtual int GetMaxMoves() const override { return ConnectFourGameState::kMaxMoves; }
    virtual void MakeMove(const Move& move) override;
    virtual Moves GetLegalMoves() const override;
    virtual int GetWinner() const override;
    virtual void PrintWinner() const override;
    virtual void ResetMove(const int& pos) override;
    virtual void Draw() const override;
    virtual int Evaluate() const override;
};
