#include "MinMaxAi.h"
#include "../Interface/Board.h"
#include  <algorithm>
#include <limits>
Move MinMaxAi::FindBestMove()
{
	int move = -1;
	int score = std::numeric_limits<int>::max();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	Moves moves(m_pBoard->GetLegalMoves());

	for (unsigned int i = 0; i < moves.size(); ++i)
	{
		m_pBoard->MakeMove(moves[i]);
		int  currentScore = Minimax(0, true, alpha, beta);

		if (currentScore < score)
		{
			score = currentScore;
			move = i;
		}
		std::min(beta, currentScore);
		m_pBoard->ResetMove(moves[i].second);

		if (beta <= alpha)
		{
			break;
		}
	}
	return moves[move];
}

int MinMaxAi::Minimax(int depth, bool isMaximizingPlayer, int alpha, int beta)
{
	Moves moves(m_pBoard->GetLegalMoves());

	if (m_pBoard->GetWinner() != 0 || moves.empty() || depth == k_maxDepth)
	{
		return Evaluate(depth);
	}

	if (isMaximizingPlayer)
	{
		int bestScore = std::numeric_limits<int>::min();

		for (auto move : moves)
		{
			m_pBoard->MakeMove(move);
			int score = Minimax(depth + 1, !isMaximizingPlayer, alpha, beta);

			bestScore = std::max(bestScore, score);
			alpha = std::max(alpha, bestScore);
			m_pBoard->ResetMove(move.second);

			if (beta <= alpha)
			{
				break;
			}
		}
		return bestScore;
	}
	else        // minimizing player
	{
		int bestScore = std::numeric_limits<int>::max();

		for (auto move : moves)
		{
			m_pBoard->MakeMove(move);
			int score = Minimax(depth + 1, !isMaximizingPlayer, alpha, beta);

			bestScore = std::min(bestScore, score);
			beta = std::min(beta, bestScore);
			m_pBoard->ResetMove(move.second);

			if (beta <= alpha)
			{
				break;
			}
		}

		return bestScore;
	}

}

int MinMaxAi::Evaluate(int depth)
{
	if (m_pBoard->GetWinner() == 1)
	{
		return std::numeric_limits<int>::max();
	}
	if (m_pBoard->GetWinner() == 2)
	{
		return std::numeric_limits<int>::min();
	}
	return m_pBoard->Evaluate();
}






