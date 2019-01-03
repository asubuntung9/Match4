// TicTacToeGameState.cpp
#include "TicTacToeGameState.h"
#include "../Interface/Types.h"
#include <iostream>
#include <assert.h>

TicTacToeGameState::TicTacToeGameState()
{
    Clear();
}

void TicTacToeGameState::Clear()
{
    memset(m_cells, 0, sizeof(TicTacToeCellState) * kBoardArraySize);
}

int TicTacToeGameState::CheckForWinner() const
{
    // rows
    for (int i = 0; i < kBoardHeight; ++i)
    {
        int baseIndex = i * kBoardWidth;
        if (m_cells[baseIndex] != TicTacToeCellState::kEmpty && m_cells[baseIndex] == m_cells[baseIndex + 1] && m_cells[baseIndex] == m_cells[baseIndex + 2])
            return static_cast<int>(m_cells[baseIndex + i]);
    }

    // columns
    for (int i = 0; i < kBoardWidth; ++i)
    {
        if (m_cells[i] != TicTacToeCellState::kEmpty && m_cells[i] == m_cells[i + kBoardWidth] && m_cells[i] == m_cells[i + (kBoardWidth * 2)])
            return static_cast<int>(m_cells[i]);
    }

    // diag
    if (m_cells[0] != TicTacToeCellState::kEmpty && m_cells[0] == m_cells[kBoardWidth + 1] && m_cells[0] == m_cells[(kBoardWidth * 2) + 2])
        return static_cast<int>(m_cells[0]);
    if (m_cells[kBoardWidth - 1] != TicTacToeCellState::kEmpty && m_cells[kBoardWidth - 1] == m_cells[kBoardWidth + 1] && m_cells[kBoardWidth - 1] == m_cells[kBoardWidth * 2])
        return static_cast<int>(m_cells[kBoardWidth - 1]);


    return 0;
}

void TicTacToeGameState::MakeMove(const Move& move)
{
    assert(move.first == 1 || move.first == 2);  // 1 == X, 2 == O
    assert(move.second >= 0 && move.second < kBoardArraySize);  // board index
    assert(m_cells[move.second] == TicTacToeCellState::kEmpty);  // must be a blank square

    m_cells[move.second] = static_cast<TicTacToeCellState>(move.first);
}

void TicTacToeGameState::ResetMove(const int &index)
{
    m_cells[index] = TicTacToeCellState::kEmpty;
}

void TicTacToeGameState::Draw() const
{
    for (int y = 0; y < kBoardHeight; ++y)
    {
        for (int x = 0; x < kBoardWidth; ++x)
        {
            int index = GetIndexFromPos(x, y);
            switch (m_cells[index])
            {
                case TicTacToeCellState::kEmpty:
                    std::cout << "_ ";
                    break;
                case TicTacToeCellState::kX:
                    std::cout << "X ";
                    break;
                case TicTacToeCellState::kO:
                    std::cout << "O ";
                    break;
                default:
                    assert(0 && "Bad cell state");
                    break;
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

Moves TicTacToeGameState::GetLegalMoves(int playerIndex) const
{
    Moves moves;
    moves.reserve(kMaxMoves);

    for (int i = 0; i < kBoardArraySize; ++i)
    {
        if (m_cells[i] == TicTacToeCellState::kEmpty)
            moves.emplace_back(std::make_pair(playerIndex, i));
    }

    return moves;
}



unsigned int TicTacToeGameState::GetHash() const
{
    unsigned int hash = 0;
    for (int i = 0; i < kBoardArraySize; ++i)
    {
        unsigned char rawVal = static_cast<unsigned char>(m_cells[i]);
        hash |= (rawVal << i * 2);
    }
    return hash;
}
