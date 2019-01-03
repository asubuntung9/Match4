// Application.h
#pragma once

// If 1, the game is tic-tac-toe.  If 0, it is connect four.
#define PLAY_TIC_TAC_TOE 0

#include "../GenericImplementations/MinMaxAi.h"
#if PLAY_TIC_TAC_TOE
    #include "../TicTacToe/TicTacToeBoard.h"
    #include "../GenericImplementations/RandomAi.h"

#else
    #include "../ConnectFour/ConnectFourBoard.h"
#endif

// If 1, the game use MinMax  If 0, the game use MCTS.
#define MIN_MAX 1


#if MIN_MAX
#include "../GenericImplementations/MinMaxAi.h"

#else
#include "../GenericImplementations/MCTS.h"
#endif



class Application
{
#if PLAY_TIC_TAC_TOE
    TicTacToeBoard m_board;
 
#else
    ConnectFourBoard m_board;
	
#endif

#if MIN_MAX
     MinMaxAi m_ai;

#else
    MCTS m_ai;

#endif
   

public:
    Application();

    void Run();

private:
    void ProcessPlayerMove(int playerIndex = 1);
    void ProcessAiMove();
    bool CheckForWinner() const;
};

