#pragma once
#include "../Interface/Board.h"
#include "../Interface/Types.h"
#include <vector>
class State 
{
    //Variables
    Board* m_pBoard;
    std::vector <State*> m_children;
    int m_visits;
    double m_value;
    Moves moves;
    State* m_pParent;

    //Method

public:
    bool IsNotFullyExpanded();
    Board* GetBoard() const { return m_pBoard; }
    std::vector <State*> GetChildren() const{ return m_children; }
    int GetVisits()const { return m_visits; }
    double GetValue() const { return m_value; }
    State* GetParent()const { return m_pParent; }
    Moves GetMoves() const { return moves; }

    void AddVisits() { m_visits++; }
    void AddValue(int amount) { m_value+= amount; }
    void SetVisits(int visits) { m_visits = visits; }
    void SetValue(int value) { m_value = value; }
    void SetParent(State* pParent) { m_pParent = pParent; }
    void AddChild(State* pChild) { m_children.push_back(pChild); }

    State(Board* pBoard) : m_pBoard(pBoard), m_visits(0), m_value(0) { moves = m_pBoard->GetLegalMoves(); }
    ~State()
    {
        for (auto child : m_children)
        {
            delete child;
        }
        delete m_pBoard;
        m_children.clear();
    }
};

