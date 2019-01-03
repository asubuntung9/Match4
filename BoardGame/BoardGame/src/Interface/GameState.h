// GameState.h
#pragma once

class GameState
{
public:
    virtual ~GameState() { }
    virtual unsigned int GetHash() const = 0;
};
