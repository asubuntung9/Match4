// ConnectFourGameState.cpp
#include "ConnectFourGameState.h"
#include <string.h>  // for memset()
#include <assert.h>
#include <iostream>  // :(
#include <cmath>
#include <limits>

ConnectFourGameState::ConnectFourGameState()
{
    Clear();
}

unsigned int ConnectFourGameState::GetHash() const
{
    return 0;
}

void ConnectFourGameState::Clear()
{
    memset(m_cells, 0, sizeof(CellState) * kBoardArraySize);
}

int ConnectFourGameState::CheckForWinner() const
{
    for (int y = 0; y < kBoardHeight; ++y)
    {
        for (int x = 0; x < kBoardWidth; ++x)
        {
            int index = GetIndexFromPos(x, y);
            CellState result = CheckForWinAt(x, y);

            if (result != CellState::kEmpty)
                return (int)result;
        }
    }

    return 0;
}

void ConnectFourGameState::MakeMove(const Move& move)
{

    assert(move.first == 1 || move.first == 2);  // 1 == red, 2 == black
    assert(move.second >= 0 && move.second < kBoardWidth);  // the column to drop the piece

    for (int y = 0; y < kBoardHeight; ++y)
    {
        int index = GetIndexFromPos(move.second, y);
        if (m_cells[index] == CellState::kEmpty)
        {
            m_cells[index] = static_cast<CellState>(move.first);
            return;
        }
    }

    assert(0 && "Not enough rows.");

}

void ConnectFourGameState::ResetMove(const int& pos)
{
	for (int y = kBoardHeight -1; y > -1; --y)
	{
		int index = GetIndexFromPos(pos, y);
		if (m_cells[index] != CellState::kEmpty)
		{
			m_cells[index] = CellState::kEmpty;

			return;
		}
	} 
}

std::vector<bool> ConnectFourGameState::GetValidColumns() const
{
    std::vector<bool> outColumns = { false, false, false, false, false, false, false };

    for (int x = 0; x < kBoardWidth; ++x)
    {
        for (int y = 0; y < kBoardHeight; ++y)
        {
            int index = GetIndexFromPos(x, y);
            if (m_cells[index] == CellState::kEmpty)
            {
                outColumns[x] = true;
                break;
            }
        }
    }

    return outColumns;
}

void ConnectFourGameState::Draw() const
{
    for (int y = kBoardHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x < kBoardWidth; ++x)
        {
            int index = GetIndexFromPos(x, y);
            switch (m_cells[index])
            {
                case CellState::kEmpty:
                    std::cout << "_ ";
                    break;
                case CellState::kRed:
                    std::cout << "X ";
                    break;
                case CellState::kBlack:
                    std::cout << "O ";
                    break;
                default:
                    assert(0 && "Bad cell state");
                    break;
            }
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}



CellState ConnectFourGameState::CheckForWinAt(int x, int y) const
{
    CellState result = CheckForConnection(x, y, 1, 0);
    if (result != CellState::kEmpty)
        return result;
    result = CheckForConnection(x, y, 0, 1);
    if (result != CellState::kEmpty)
        return result;
    result = CheckForConnection(x, y, 1, 1);
    if (result != CellState::kEmpty)
        return result;
    result = CheckForConnection(x, y, 1, -1);
    if (result != CellState::kEmpty)
        return result;

    return CellState::kEmpty;
}

CellState ConnectFourGameState::CheckForConnection(int x, int y, int dx, int dy) const
{
    int index = GetIndexFromPos(x, y);
    const CellState testState = m_cells[index];

    for (int i = 1; i < kWinCount; ++i)
    {
        // recalculate x & y for the new position
        int testX = x + i * dx;
        int testY = y + i * dy;

        // Make sure they're in bounds.  If not, this can't be a connection.
        if (testX < 0 || testX >= kBoardWidth)
            return CellState::kEmpty;
        if (testY < 0 || testY >= kBoardHeight)
            return CellState::kEmpty;

        // if we get here, check to see if this could possibly be another connection
        index = GetIndexFromPos(testX, testY);
        if (m_cells[index] != testState)
            return CellState::kEmpty;
    }

    // If we get here, we have a connection.  Return the cellstate.
    return testState;
}

int ConnectFourGameState::GetBoardScore() const
{
    return GetTotalStreaks(2) + GetTotalStreaks(3);
}

int ConnectFourGameState::GetTotalStreaks(int streaks) const
{
    int score = 0;
    for (int x = 0; x < kBoardWidth; ++x)
    {
        for (int y = 0; y < kBoardHeight; ++y)
        {   
            int index = GetIndexFromPos(x, y);
            score += CheckForStreaks(streaks, x, y, 1, 0);
            score += CheckForStreaks(streaks, x, y, 0, 1);
            score += CheckForStreaks(streaks, x, y, 1, 1);
            score += CheckForStreaks(streaks, x, y, 1, -1);
        }
    }

    return score;
}


int ConnectFourGameState::CheckForStreaks(int streaks, int x, int y, int dx, int dy) const
{
    int index = GetIndexFromPos(x, y);
    const CellState testState = m_cells[index];

    for (int i = 1; i < streaks; ++i)
    {
        // recalculate x & y for the new position
        int testX = x + i * dx;
        int testY = y + i * dy;

        // Make sure they're in bounds.  If not, this can't be a connection.
        if (testX < 0 || testX >= kBoardWidth)
            return 0;
        if (testY < 0 || testY >= kBoardHeight)
            return 0;

        // if we get here, check to see if this could possibly be another connection
        index = GetIndexFromPos(testX, testY);
        if (m_cells[index] != testState)
            return 0;
    }

    // If we get here, we have a connection.  Return 1.
    if (testState == CellState::kRed)
    {
        return (int)(std::pow(10, streaks*streaks));
    }
    else
    {
        return (int)(std::pow(10, streaks*streaks) * -1);
    }
}




