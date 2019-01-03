#include "MCTS.h"
#include <math.h>


MCTS::~MCTS()
{
}

Move MCTS::FindBestMove()
{   
    State* currentState = new State(m_pBoard);
    MCTS_Sample(currentState);
    int move = GetBestMove(currentState);
    Moves moves = m_pBoard->GetLegalMoves();

    return moves[move];
}

int MCTS::MCTS_Sample(State* pState)
{
    pState->AddVisits();
    int winner;
    State* next_state;

    if (!pState->IsNotFullyExpanded())
    {
        State* next_state = UCB_Sample(pState);
        winner = MCTS_Sample(next_state);
    }
    else
    {
         if (pState->IsNotFullyExpanded())
         {
             next_state = Expand(GetRandomUnexpandedChild(pState));
         }
         else
         {
             next_state = pState;
         }
         winner = RandomPlayout(next_state);
    }
   
    UpdateValue(pState, winner);

    return winner;
}

//UCB sample
State* MCTS::UCB_Sample(State* pState)
{
    std::vector <int> weights;
    for (auto child: pState->GetChildren())
    {
        int w = child->GetValue() + 2* std::sqrt(std::log(pState->GetVisits()) / child->GetVisits());
        weights.push_back(w);
             
    }
    return pState;
  
}
//Node expansion

State* MCTS::Expand(State* pState)
{   
    pState->SetVisits(1);
    pState->SetValue(0);
    return pState;
}


//rollout
int MCTS::RandomPlayout(State* pState)
{
    if (pState->GetBoard()->GetWinner()!= 0)
    {
        return pState->GetBoard()->GetWinner();
    }
    else
    {   
        int val = RandomPlayout(RandomMove(pState));
     
        return val;
    }
}

void MCTS::UpdateValue(State* pState, int winner)
{
    if (pState->GetBoard()->GetWinner() == winner)
    {
        pState->AddValue(1);
    }
    else
    {
        pState->AddValue(-1);
    }
}

State*  MCTS::RandomMove(State*  pState)
{
    Moves moves(pState->GetBoard()->GetLegalMoves());

    int choice = rand() % moves.size();
    pState->GetBoard()->MakeMove(moves[choice]);

    return pState;
}

State * MCTS::GetRandomUnexpandedChild(State * pState)
{
    Moves moves = pState->GetMoves();
    int choice = rand() % moves.size();
    
    Board* childBoard = new ConnectFourBoard();

    //copy board
    memcpy(childBoard, pState->GetBoard(), sizeof(pState->GetBoard()));

    State* pChild = new State(childBoard);
    pChild->GetBoard()->MakeMove(moves[choice]);

    pChild->SetParent(pState);
    pState->AddChild(pChild);

    return pChild;
}

int MCTS::GetBestMove(State * pState)
{
    for (auto child : pState->GetChildren())
    {
        //find one with biggest value
    }
    return 0;
}


