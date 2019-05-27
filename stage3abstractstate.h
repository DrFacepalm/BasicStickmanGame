#pragma once

#include "gamestate.h"

class Stage3AbstractState : public GameState
{
public:
    virtual void nextState() = 0;
};

