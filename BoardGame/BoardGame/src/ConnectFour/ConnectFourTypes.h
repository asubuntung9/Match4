// ConnectFourTypes.h
#pragma once

enum class CellState : unsigned char
{
    kEmpty  = 0,
    kRed    = 1,  // must be 1, since it corresponds to player 1
    kBlack  = 2,  // must be 2, since it corresponds to player 2
};
