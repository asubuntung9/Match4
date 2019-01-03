// TicTacToeBoard.cpp
#include "TicTacToeBoard.h"
#include <iostream>

TicTacToeBoard::TicTacToeBoard()
    : m_currentPlayer(Player::kX)
{
    //
}

void TicTacToeBoard::StartGame()
{
    m_currentState.Clear();
}

void TicTacToeBoard::MakeMove(const Move& move)
{
    m_currentState.MakeMove(move);
    m_currentPlayer = (m_currentPlayer == Player::kX ? Player::kO: Player::kX);
}

void TicTacToeBoard::PrintWinner() const 
{
    switch (GetWinner())
    {
        case 0:
            std::cout << "\n*** Tie ***\n";
            break;

        case 1:
            std::cout << "*** X Has Won! ***\n";
            break;

        case 2:
            std::cout << "*** O Has Won! ***\n";
            break;

        default:
            std::cout << "*** ERROR ***\n";
            break;
    }
}

void TicTacToeBoard::ResetMove(const int& index)
{
    m_currentState.ResetMove(index);
m_currentPlayer = (m_currentPlayer == Player::kX ? Player::kO : Player::kX);
}

void TicTacToeBoard::Draw() const
{
	m_currentState.Draw();

	if (m_currentPlayer == Player::kX)
		std::cout << "X to move.\n";
	else if (m_currentPlayer == Player::kO)
		std::cout << "O to move.\n";
	else
		std::cout << "Unknown move...\n";
}

int TicTacToeBoard::Evaluate() const
{
	int score = 0;

	// check 2 in a rows

	//rows
	for (int i = 0; i < kBoardWidth; ++i)
	{
		int baseIndex = i * kBoardHeight;

		if (m_currentState.GetCellAtIndex(baseIndex + 1) != TicTacToeCellState::kEmpty)
		{
			if (m_currentState.GetCellAtIndex(baseIndex + 2) == m_currentState.GetCellAtIndex(baseIndex + 1))
			{
				if ((int)m_currentState.GetCellAtIndex(baseIndex + 1) == 1)
				{
					score += 10;
				}
				else
				{
					score -= 10;
				}
			}
			if (m_currentState.GetCellAtIndex(baseIndex) == m_currentState.GetCellAtIndex(baseIndex + 1))
			{
				if ((int)m_currentState.GetCellAtIndex(baseIndex + 1) == 1)
				{
					score += 10;
				}
				else
				{
					score -= 10;
				}
			}
		}

	}

	// columns
	for (int i = 0; i < kBoardHeight; ++i)
	{
		if (m_currentState.GetCellAtIndex(i + kBoardWidth) != TicTacToeCellState::kEmpty)
		{
			if (m_currentState.GetCellAtIndex(i) == m_currentState.GetCellAtIndex(i + kBoardWidth))
			{
				if ((int)m_currentState.GetCellAtIndex(i + kBoardWidth) == 1)
				{
					score += 10;
				}
				else
				{
					score -= 10;
				}
			}
			if (m_currentState.GetCellAtIndex(i + kBoardWidth) == m_currentState.GetCellAtIndex(i + (kBoardWidth * 2)))
			{
				if ((int)m_currentState.GetCellAtIndex(i + kBoardWidth) == 1)
				{
					score += 10;
				}
				else
				{
					score -= 10;
				}
			}
		}

	}

	// diag
	if (m_currentState.GetCellAtIndex(kBoardWidth + 1) != TicTacToeCellState::kEmpty)
	{
		if (m_currentState.GetCellAtIndex(0) == m_currentState.GetCellAtIndex(kBoardWidth + 1))
		{
			if ((int)m_currentState.GetCellAtIndex(kBoardWidth + 1) == 1)
			{
				score += 10;
			}
			else
			{
				score -= 10;
			}
		}
		if (m_currentState.GetCellAtIndex(kBoardWidth + 1) == m_currentState.GetCellAtIndex((kBoardWidth * 2) + 2))
		{

			if ((int)m_currentState.GetCellAtIndex(kBoardWidth + 1) == 1)
			{
				score += 10;
			}
			else
			{
				score -= 10;
			}
		}

	}      
  
	if (m_currentState.GetCellAtIndex(kBoardWidth + 1) != TicTacToeCellState::kEmpty)
	{
		if (m_currentState.GetCellAtIndex(kBoardWidth * 2) == m_currentState.GetCellAtIndex(kBoardWidth + 1))
		{

			if ((int)m_currentState.GetCellAtIndex(kBoardWidth + 1) == 1)
			{
				score += 10;
			}
			else
			{
				score -= 10;
			}
		}
		if (m_currentState.GetCellAtIndex(kBoardWidth + 1) == m_currentState.GetCellAtIndex(kBoardWidth * 2))
		{

			if ((int)m_currentState.GetCellAtIndex(kBoardWidth + 1) == 1)
			{
				score += 10;
			}
			else
			{
				score -= 10;
			}
	  }
	}

    return score;
}






