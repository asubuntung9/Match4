#pragma once

#include "../Interface/GameAi.h"
#include "../Interface/Board.h"

#include "../GenericImplementations/State.h"
#define PLAY_TIC_TAC_TOE 0


#if PLAY_TIC_TAC_TOE
#include "../TicTacToe/TicTacToeBoard.h"


#else
#include "../ConnectFour/ConnectFourBoard.h"
#endif

class MCTS:GameAi
{

    int MCTS_Sample(State* pState);

    State* Expand(State* pState);

    State* UCB_Sample(State* pState);

    int RandomPlayout(State* pState);

    void UpdateValue(State* pState, int winner);

    State* RandomMove(State * pState);

    State* GetRandomUnexpandedChild(State* pState);

    int GetBestMove(State* pState);

public:

    virtual Move FindBestMove() override;

    
    MCTS(Board* pBoard) : GameAi(pBoard) { }

    ~MCTS();


  
};

