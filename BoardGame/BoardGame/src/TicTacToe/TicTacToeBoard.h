// TicTacToeBoard.h
#pragma once

#include "../Interface/Board.h"
#include "TicTacToeGameState.h"


class TicTacToeBoard : public Board
{
    enum class Player : unsigned char
    {
        kX = 1,  // must be 1, since it corresponds to player 1
        kO = 2,  // must be 2, since it corresponds to player 2
    };

    TicTacToeGameState m_currentState;
    Player m_currentPlayer;


    static constexpr int kBoardWidth = 3;
    static constexpr int kBoardHeight = 3;

public:
    TicTacToeBoard();

    virtual void StartGame() override;
    virtual int GetCurrentPlayer() const override { return (int)m_currentPlayer; }
    virtual int GetMaxMoves() const override { return TicTacToeGameState::kMaxMoves; }
    virtual void MakeMove(const Move& move) override;
    virtual Moves GetLegalMoves() const override { return m_currentState.GetLegalMoves((int)m_currentPlayer); }
    virtual int GetWinner() const override { return m_currentState.CheckForWinner(); }
    virtual void PrintWinner() const override;
    virtual void ResetMove(const int&) override;
    virtual void Draw() const override;
    virtual int Evaluate() const override;

};
